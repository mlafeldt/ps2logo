/*
 * Copyright (C) 2013 Mathias Lafeldt <mathias.lafeldt@gmail.com>
 *
 * This file is part of ps2logo, the PS2 logo decryptor.
 *
 * ps2logo is licensed under the terms of the MIT License. See LICENSE file.
 */

package main

import "testing"

var encLogo = []byte{
	0x74, 0x03, 0xe6, 0x6d, 0xa0, 0x11, 0xf9, 0x55,
	0x7f, 0x2d, 0xc6, 0x61, 0x3e, 0xe6, 0x1c, 0xb4,
}
var rawLogo = []byte{
	0x00, 0xbb, 0x94, 0xc8, 0xa6, 0x2b, 0x6c, 0x09,
	0x58, 0xca, 0x95, 0xa8, 0x52, 0x94, 0x43, 0x06,
}

func TestDecryptLogo(t *testing.T) {
	want := rawLogo

	logo := make([]byte, len(encLogo))
	copy(logo, encLogo)
	decryptLogo(logo)

	for i, b := range logo {
		if b != want[i] {
			t.Errorf("expected byte #%d to be 0x%02x, got 0x%02x", i, want[i], b)
		}
	}
}

func TestEncryptLogo(t *testing.T) {
	want := encLogo
	key := encLogo[0]

	logo := make([]byte, len(rawLogo))
	copy(logo, rawLogo)
	encryptLogo(logo, key)

	for i, b := range logo {
		if b != want[i] {
			t.Errorf("expected byte #%d to be 0x%02x, got 0x%02x", i, want[i], b)
		}
	}
}
