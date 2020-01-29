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
    int help = 0;
    string limit;
    int c, idxopt;

	struct option t_opt[] =
	{
		{"help",			no_argument,			&help,		1},
        {"countdown",		required_argument,		NULL,		'c'},
        {0,         		0,              		NULL,		0}
	};
	
	while ((c = getopt_long(argc, argv, "hc:", t_opt, &idxopt)) != -1){
		switch (c){
            case 'c':
                limit = optarg;
                break;
			case 'h':
				help = 1;
				break;
			default:
				break;
		}
  	}

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
                cout << '\r' << sw.remaining_HHMMSSZZZ() << flush;
                std::this_thread::sleep_for(Stopwatch::ms(100));    
            }
            cout << '\r' << sw.remaining_HHMMSSZZZ() << flush;
            cout << '\a';
        } catch (const std::invalid_argument& e) {
            cout << "Invalid countdown format, must be hh:mm:ss";
        }
    } else {
        // Start the chrono
        sw.start();

        while (1){
            cout << '\r' << sw.elapsed_HHMMSSZZZ() << flush;
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
        "Example of use:\n"
        << progname << endl
        << progname << " --countdown 00:00:10";
}
