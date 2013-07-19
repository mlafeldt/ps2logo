ps2logo
=======

The first 12 sectors of every PS2 game disc contain the PS2 boot logo in a
slightly encrypted form. You can use ps2logo to decrypt a sector dump, and then
convert the raw image to JPEG or other formats.

(For more information, I recommend reading [ps2boot.txt] written by loser.)


Installation
------------

First, make sure you have [Go 1] installed.

To download and install ps2logo from source, simply run:

    $ go get github.com/mlafeldt/ps2logo

This should install the ps2logo command to `$GOPATH/bin/ps2logo`.

(You can find the original C implementation of ps2logo inside the [alt]
directory.)


Usage
-----

    usage: ps2logo <input file> <output file>

This will decrypt the encrypted logo in _input file_ and write it to _output
file_.


Example
-------

This example is for Linux users. On Windows, you can alternatively use Hex
Workshop to dump the sectors and Paint Shop Pro to convert the image.

To extract the logo from a PS2 game disc, do the following:

Dump the first 12 sectors of the disc:

    $ dd if=/dev/cdrom of=logo.enc bs=2048 count=12

Decrypt the sector dump with ps2logo:

    $ ps2logo logo.enc logo.raw

Use ImageMagick to convert the raw image to JPEG:

    $ convert -depth 8 -size 344x71 gray:logo.raw logo.jpg

(Note that the image width and height depend on the region: 344x71 for PAL and
384x64 for NTSC.)

Open the file in a picture viewer and you should finally see the PS2 logo.


License
-------

ps2logo is licensed under the terms of the MIT License. See [LICENSE] file.


Contact
-------

* Web: <http://mlafeldt.github.com/ps2logo>
* Mail: <mathias.lafeldt@gmail.com>
* Twitter: [@mlafeldt](https://twitter.com/mlafeldt)


[Go 1]: http://golang.org/doc/install
[LICENSE]: https://github.com/mlafeldt/ps2logo/blob/master/LICENSE
[alt]: https://github.com/mlafeldt/ps2logo/tree/master/alt
[ps2boot.txt]: https://github.com/mlafeldt/ps2logo/blob/master/Documentation/ps2boot.txt
