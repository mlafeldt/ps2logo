/*
 * Copyright (C) 2013 Mathias Lafeldt <mathias.lafeldt@gmail.com>
 *
 * This file is part of ps2logo, the PS2 logo decryptor.
 *
 * ps2logo is licensed under the terms of the MIT License. See LICENSE file.
 */

package main

import (
	"bufio"
	"io"
	"io/ioutil"
	"log"
	"os"
)

// Size of PS2 logo in bytes: 12 sectors x 2048 bytes
const LogoSize = (12 * 2048)

func readLogo(filename string) ([]byte, error) {
	f, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	defer f.Close()

	r := bufio.NewReader(f)
	logo := make([]byte, LogoSize)
	_, err = io.ReadFull(r, logo)
	return logo, err
}

func writeLogo(filename string, logo []byte) error {
	return ioutil.WriteFile(filename, logo, 0644)
}

func encryptLogo(logo []byte, key byte) {
	for i := 0; i < len(logo); i++ {
		logo[i] = ((logo[i] << 5) | (logo[i] >> 3)) ^ key
	}
}

func decryptLogo(logo []byte) {
	key := logo[0]
	for i := 0; i < len(logo); i++ {
		logo[i] ^= key
		logo[i] = (logo[i] << 3) | (logo[i] >> 5)
	}
}

func main() {
	log.SetFlags(0)

	args := os.Args[1:]
	if len(args) < 2 {
		log.Fatal("usage: ps2logo <input file> <output file>")
	}

	logo, err := readLogo(args[0])
	if err != nil {
		log.Fatal("error: failed to read logo: ", err)
	}

	decryptLogo(logo)

	if err := writeLogo(args[1], logo); err != nil {
		log.Fatal("error: failed to write logo: ", err)
	}
}
