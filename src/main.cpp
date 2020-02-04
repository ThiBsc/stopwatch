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
    int help = 0, milliseconds = 1;
    string countdown, format = "%T";
    // To change stopwatch color (works on UNIX)
    string fg, bg, color, reset;

	struct option t_opt[] =
	{
		{"help",		no_argument,			&help,		    1},
        {"ms",	    	no_argument,			&milliseconds,  0},
        {"fg",          required_argument,		NULL,		    't'},
        {"bg",		    required_argument,		NULL,		    'b'},
        {"countdown",	required_argument,		NULL,		    'c'},
        {"format",  	required_argument,		NULL,		    'f'},
        {0,         	0,              		NULL,		    0}
	};
	
	while ((c = getopt_long(argc, argv, "hmc:p:f:t:b:", t_opt, &idxopt)) != -1){
		switch (c){
			case 'h': help = 1;
				break;
            case 'm': milliseconds = 0;
				break;
            case 'c': countdown = optarg;
                break;
            case 'f': format = optarg;
				break;
#ifdef __unix__
            case 't': fg = optarg;
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
    } else if (!isatty(STDIN_FILENO)){
        // We want to measure the execution time of a program (piped)
        sw.start();
        
        char buffer[1];
        while (read(STDIN_FILENO, buffer, sizeof(buffer)) > 0) cout << buffer;
        
        // To compensate for a slight advance in the tube process
        sw.addMsecs(Stopwatch::ms(10));

        cout << color << '\r' << sw.elapsed(format.c_str(), milliseconds) << reset << flush;
    } else if (!countdown.empty()){
        // hh:mm:ss
        int h, m, s;
        h = m = s = 0;
        try {
            h = stoi(countdown.substr(0, 2));
            m = stoi(countdown.substr(3, 5));
            s = stoi(countdown.substr(6, 8));

            // Init values
            Stopwatch::hrs dh(h);
            Stopwatch::mins dm(m);
            Stopwatch::secs ds(s);
            Stopwatch::ms countdown(dh + dm + ds);
            Stopwatch::ms timeout(0);

            // Start the countdown
            sw.start(countdown);

            while (sw.remaining() > timeout){
                cout << color << '\r' << sw.remaining(format.c_str(), milliseconds) << reset << flush;
                std::this_thread::sleep_for(Stopwatch::ms(100));    
            }
            cout << color << '\r' << sw.remaining(format.c_str(), milliseconds) << reset << flush;
            cout << '\a';
        } catch (const std::exception&  e) {
            cout << "Invalid countdown format, must be hh:mm:ss";
        }
    } else {
        // Start the chrono
        sw.start();

        while (1){
            cout << color << '\r' << sw.elapsed(format.c_str(), milliseconds) << reset << flush;
            std::this_thread::sleep_for(Stopwatch::ms(100));
        }
    }

    cout << endl;

    return 0;
}

void print_help(){
    cout << "Usage: " << progname << "\n"
        "\t--help, \t-h\t Show help\n"
        "\t--ms, \t\t-m\t Hide milliseconds\n"
        "\t--countdown, \t-c\t [hh:mm:ss]\n"
        "\t--format, \t-f\t Display format (default: %T with milliseconds)\n"
        "\t\t\t\t https://en.cppreference.com/w/cpp/io/manip/put_time\n"
#ifdef __unix__
        "\t--fg, \t\t-t \t [30-37;90-97] Change the foreground color\n"
        "\t--bg, \t\t-b \t [40-47;100-107] Change the background color\n"
#endif
        "Example of use:\n"
        << progname << endl
#ifdef __unix__
        << progname << " --fg 97" << endl
        << progname << " --fg 97 --bg 46" << endl
#endif
        << progname << " --countdown 00:00:10" << endl
        << progname << " --format %H:%M:%S";
}
