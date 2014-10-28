# Dawkins' Network Weasel

Dnweasel is a networked version of [Dawkin's weasel algorithm](http://en.wikipedia.org/wiki/Weasel_program). The client starts by sending a chosen string over the network to the server, and then the two components apply Dawkin's algorithm to the string and send it back after a certain delay.

## Usage

The main binary is `dnweasel`. Another binary, `weasel_test` is provided to test out the weasel algorithm.

```
$ ./dnweasel
Usage: Listen for inbound:	./dnweasel -l [-p port]
	Connect to somewhere:	./dnweasel -h hostname [-t target string] [-p port]

$ ./weasel_test -h
Usage: ./weasel_test [OPTIONS]
	-m, --message	Target string (METHINKS IT IS LIKE A WEASEL)

```

Execute the program server-side by running `./dnweasel -l`. Then execute the program client-side by running

`./dnweasel -h <host>`

```
$ ./dnweasel -l
Listening on port 8376
> 127.0.0.1: METHINKS IT IS LIKE A WEASEL
> 127.0.0.1: GCPGWIOICMIVFCQW J DCXUGACZL
< 127.0.0.1: GWPGWIOICMIVFCQW J DC UGACZL (score: 3)
> 127.0.0.1: GWPGWIOICMIVFSQW J DC UGACZL
< 127.0.0.1: GWPGIIOICMIVFSQW J DC UGACZL (score: 5)

...

$ ./dnweasel -h 127.0.0.1
Connecting to 127.0.0.1...
< 127.0.0.1: METHINKS IT IS LIKE A WEASEL
< 127.0.0.1: GCPGWIOICMIVFCQW J DCXUGACZL (score: 2)
> 127.0.0.1: GWPGWIOICMIVFCQW J DC UGACZL
< 127.0.0.1: GWPGWIOICMIVFSQW J DC UGACZL (score: 4)
> 127.0.0.1: GWPGIIOICMIVFSQW J DC UGACZL

```