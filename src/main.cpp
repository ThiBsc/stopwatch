#include <iostream>
#include <thread>
#include <getopt.h>
#include <unistd.h>
#include "header/stopwatch.h"

using namespace std;

const string progname = "sw";

void print_help();

int main(int argc, char *argv[])
{
    int c, idxopt;
    int help = 0;
    string limit;
    // To change stopwatch color (works on UNIX)
    string fg, bg, color, reset;

	struct option t_opt[] =
	{
		{"help",		no_argument,			&help,		1},
        {"fg",          required_argument,		NULL,		'f'},
        {"bg",		    required_argument,		NULL,		'b'},
        {"countdown",	required_argument,		NULL,		'c'},
        {0,         	0,              		NULL,		0}
	};
	
	while ((c = getopt_long(argc, argv, "hc:", t_opt, &idxopt)) != -1){
		switch (c){
			case 'h': help = 1;
				break;
            case 'c': limit = optarg;
                break;
#ifdef __unix__
            case 'f': fg = optarg;
				break;
            case 'b': bg = optarg;
				break;
#endif
			default:
				break;
		}
  	}

#ifdef __unix__
    if (!fg.empty()){
        color = fg;
    }
    if (!bg.empty()){
        color += (color.empty() ? bg : ";"+bg);
    }
    if (!color.empty()){
        color.insert(0, "\033[");
        color.push_back('m');
        reset = "\033[0m";
    }
#endif

    // Instantiate the stopwatch
    Stopwatch sw;

    if (help){
        print_help();
    } else if (!limit.empty()){
        // hh:mm:ss
        int h, m, s;
        h = m = s = 0;
        try {
            h = stoi(limit.substr(0, 2));
            m = stoi(limit.substr(3, 5));
            s = stoi(limit.substr(6, 8));

            // Init values
            Stopwatch::hrs dh(h);
            Stopwatch::mins dm(m);
            Stopwatch::secs ds(s);
            Stopwatch::ms countdown(dh + dm + ds);
            Stopwatch::ms timeout(0);

            // Start the countdown
            sw.start(countdown);

            while (sw.remaining() > timeout){
                cout << color << '\r' << sw.remaining_HHMMSSZZZ() << reset << flush;
                std::this_thread::sleep_for(Stopwatch::ms(100));    
            }
            cout << '\r' << "00:00:00.000" << flush;
            cout << '\a';
        } catch (const std::exception&  e) {
            cout << "Invalid countdown format, must be hh:mm:ss";
        }
    } else {
        // Start the chrono
        sw.start();

        while (1){
            cout << color << '\r' << sw.elapsed_HHMMSSZZZ() << reset << flush;
            std::this_thread::sleep_for(Stopwatch::ms(100));
        }
    }

    cout << endl;

    return 0;
}

void print_help(){
    cout << "Usage: " << progname << "\n"
        "\t--help, \t-h\t Show help\n"
        "\t--countdown, \t-c\t [hh:mm:ss]\n"
#ifdef __unix__
        "\t--fg \t\t\t [30-37;90-97] Change the foreground color\n"
        "\t--bg \t\t\t [40-47;100-107] Change the background color\n"
#endif
        "Example of use:\n"
        << progname << endl
#ifdef __unix__
        << progname << " --fg 97" << endl
        << progname << " --fg 97 --bg 46" << endl
#endif
        << progname << " --countdown 00:00:10";
}
