# A Trivial Web Server

The world's first publicly visible website http://info.cern.ch was 
launched on December 20, 1990. That makes the web 25 years old since
it's launch. 

To celebrate the event, I wrote a trivial web server in C. The
web server is really simply. It always returns the same response.
The code is < 100 lines of C. 

This demonstrates the elegance and beauty of Tim Berners Lee's 
hypertext sytem and the HTTP protocol he invented. Anyone
could put together a functioning webserver with very little
effort and it would instantly become part of a vast global
network.


## Building and running the code

You need a machine with a modern C compiler. I've tested this with
GNU gcc v4.8.3 on CentOS 7.

You can build the code with the following command:

    make 


You can run the code with the following command:

    ./trivialhttpd



By default the the web server can be accessed on port 8004
Change the port number in the code if you want it listen
on any other port.


The webserver can be accessed as http://hostname:8004
where the hostname is the hostname or IP address of the machine
where this program is running. To access the server from
a web browser on the same machine, use the following URL:

http://localhost:8004

Note that you may have to instruct the firewall on the
machine running this web server to allow external programs
to connect to it.


## Credits

[Tim Berners-Lee](https://en.wikipedia.org/wiki/Tim_Berners-Lee) for inventing the web.

W Richard Stevens really wonderful text on [Unix Network Programming](http://www.amazon.com/Unix-Network-Programming-Volume-Networking/dp/0131411551).
The book is as relevant now as it was when it was first written
more than 20 years ago.

