use std::env;
use std::fs::File;
use std::io;
use std::io::prelude::*;
use std::path::Path;
use std::process;

fn main() {
    let args: Vec<String> = env::args().skip(1).collect();
    if args.len() != 2 {
        eprintln!("usage: ps2logo <input file> <output file>");
        process::exit(1);
    }

    let mut logo = vec![0xca; LOGO_SIZE].into_boxed_slice();

    if let Err(err) = read_logo(Path::new(&args[0]), &mut logo) {
        eprintln!("error: failed to read logo: {}", err);
        process::exit(1);
    }

    decrypt_logo(&mut logo);

    if let Err(err) = write_logo(Path::new(&args[1]), &logo) {
        eprintln!("error: failed to write logo: {}", err);
        process::exit(1);
    }
}

fn read_logo(path: &Path, buf: &mut [u8]) -> Result<(), io::Error> {
    File::open(path)?.read_exact(buf)
}

fn write_logo(path: &Path, buf: &[u8]) -> Result<(), io::Error> {
    File::create(path)?.write_all(buf)
}

fn decrypt_logo(logo: &mut [u8]) {
    let key = logo[0];
    for x in logo {
        *x ^= key;
        *x = (*x << 3) | (*x >> 5);
    }
}

// Size of PS2 logo in bytes: 12 sectors x 2048 bytes
const LOGO_SIZE: usize = 12 * 2048;
