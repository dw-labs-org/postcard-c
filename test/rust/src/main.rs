#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
#![allow(unused)]

use std::mem::MaybeUninit;

mod postcard_cobs;

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

fn main() {}

#[derive(Debug)]
pub struct Cobs<const N: usize> {
    pub buf: Box<[u8; N]>,
    pub cobs: cobs_encoder,
}

impl<const N: usize> Cobs<N> {
    fn new() -> Self {
        let mut buf = Box::new([0u8; N]);
        let mut cobs = MaybeUninit::<cobs_encoder>::uninit();
        let cobs = unsafe {
            cobs_encoder_init(cobs.as_mut_ptr(), &mut *buf as *mut u8, N as u32);
            cobs.assume_init()
        };
        Self { buf, cobs }
    }

    fn start_frame(&mut self) {
        unsafe { cobs_encoder_start_frame(&mut self.cobs as *mut cobs_encoder) }
    }

    fn end_frame(&mut self) {
        unsafe {
            cobs_encoder_end_frame(&mut self.cobs as *mut cobs_encoder);
        }
    }

    fn reset(&mut self) {
        unsafe { cobs_encoder_reset(&mut self.cobs as *mut cobs_encoder) };
    }

    fn write_byte(&mut self, byte: u8) {
        unsafe { cobs_encoder_write_byte(&mut self.cobs as *mut cobs_encoder, byte) };
    }
}
