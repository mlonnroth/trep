# trep
Command-line time-reporting utility. Use this to quickly calculate your working hours during a day.

Usage:  trep start [stop] [lunch]
        start/stop format hhmm
        lunch format mm

'trep 745 1615 30' means you came at 07:45 and left at 16:15 with a 30 minutes lunch.
That's 8 hours of work.

Default values: if not specified, stop defaults to 1600 and lunch to 15
