# About

`doctolib-cli` is a command line program to interact with the Doctolib website.
Doctolib is used in France, Germany, and Italy to book medical appointments
online.

## How to build/install/use

1. Build the binary
```shell
 $ ./build.sh
```

2. (optional, not recomended) Install the binary
```shell
 # install doctolib-cli /usr/bin/
```

3. Run the program
```shell
 # List "Médecins généralistes" from Strasbourg, France
 $ doctolib-cli find-specialist "généraliste" "strasbourg"

 # Show infos about a specific doctor/hospital/...
 $ doctolib-cli show-profile [NAME]
```

# TODO

## To make the program usable

* Do not hardcode base URL (allow switching to doctolib.fr/doctolib.de/doctolib.it
  at runtime.)
* Better parsing to show more data
* Better argument parsing
* Add help prompt
* Better error handling

## Future plans

* Support loging in to an account
* Book an appointment with the logged-in account
* List upcoming appointments for the logged-in account
* Interactive mode
* Colors

### Is this even possible?

There seem to be a whole separate API for the doctor's side of the website.
It would be super nice to get this to work with the program... This is the
"end game goal", I have no intention of working on this any time soon, plus, I'm
not a doctor, and I don't think I can create a doctor account. If someone has
access to such an account, it'd be fun to reverse-engeneer this part of the API
too tho... 👀
