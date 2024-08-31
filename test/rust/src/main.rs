#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

use std::{mem::MaybeUninit, ops::DerefMut};

mod postcard_cobs;

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

fn main() {}

#[derive(Debug)]
pub struct Cobs<const N: usize> {
    pub buf: Box<[u8; N]>,
    pub cobs: cobs,
}

impl<const N: usize> Cobs<N> {
    fn new() -> Self {
        let mut buf = Box::new([0u8; N]);
        let mut cobs = MaybeUninit::<cobs>::uninit();
        let cobs = unsafe {
            cobs_init(cobs.as_mut_ptr(), &mut *buf as *mut u8, 256);
            cobs.assume_init()
        };
        Self { buf, cobs }
    }

    fn start_frame(&mut self) {
        unsafe { cobs_start_frame(&mut self.cobs as *mut cobs) }
    }

    fn end_frame(&mut self) {
        unsafe { cobs_end_frame(&mut self.cobs as *mut cobs) }
    }

    fn reset(&mut self) {
        unsafe { cobs_reset(&mut self.cobs as *mut cobs) };
    }

    fn write_byte(&mut self, byte: u8) {
        unsafe { cobs_write_byte(&mut self.cobs as *mut cobs, byte) };
    }
}
