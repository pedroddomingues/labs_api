<!-- ## Script to get JWT token
```bash
curl -X POST --data "grant_type=client_credentials&client_id=CLIENT-ID&client_secret=CLIENT-SECRET" https://api.intra.42.fr/oauth/token
```
curl -X POST --data "grant_type=client_credentials&client_id=93ae758ab8266f7c4c419e58a605ea217aef2dd5c0776ac38521328dd9f0391f&client_secret=13c0e6d41d35465e40dbe6a1c67165c59940dc141c3443ddd9484b562187a7a9" https://api.intra.42.fr/oauth/token -->
# 42sp_labs
This project was done to match the 42sp labs program challenge.
The goal is to consume the 42.fr API and fetch user data with the provided login, store that data in a database and some analysis.

Using C is the only rule for that challenge.

# How to use the program
## Dependencies
This program depends on c libraries: libcurl, pqsql and json-c.

A static library is provided but tested only in Debian-dists devices, so make sure you have them installed when recompiling the library.
## Compile
Run ```make linux``` to create the executable program for linux using the static library.

Run ```make mac``` to create the executable program for mac using the static library.

After that you can run ``make run [?token]`` to run the executable.
The token is optional, if you don't provide, you will be asked with your UID and SECRET from intra.

# My approach
I didn't subscribe to the program but I've tried to do the challenge anyway.
At first I thought the requested was a client side program but in the last day I realized that it should be an backend API serving HTTP, so in the last day I'm trying to do that. The command line program is still present.

The process sequence I have in mind is

``get login from user -> fetch database data for that user -> save it in database -> do some analysis -> return data and analysis to the user``

Files and functions were written to be as modular as I could, this doesn't seem that good but as I write this I can see how to share the functions and structs made for the shell program with the API backend.

## Techs
**Postgresql**

Was chosen to be the database type because it's opensource and a relational database.

**AWS**

RDS database to host the postgres database.

## C Libraries

**libcurl**

The most used network transfer client side library for C.

**libpq**

Official postgres library for C.

**json-c**

The simplest json parser for C.

# What I've learned so far
- How to use external libraries in c programs.
- How to use those libraries: libcurl, libpq, json-c.
- How to setup an AWS RDS database with budget (lost $25 to learn) and how to manage its security access and logs.
- How to use pgAdmin to manage a postgres database.
- Some SQL syntax and structure doing queries.
- Lots of memory management with mallocs and frees and AAAAAAAAAAAA SEGFAULT.
- Read the proposal statement more carefully.

## todo
- Include more columns in the database to have more rich data.
- Implement user-cursus related data.
- Apply runtime filters.
- Do more analysis to point important data.
