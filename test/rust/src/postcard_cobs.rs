use crate::{cobs, postcard_cobs_encode_u16, postcard_cobs_encode_u8, Cobs};

struct PostcardCobs<const N: usize> {
    pub cobs: Cobs<N>,
}

impl<const N: usize> PostcardCobs<N> {
    fn new() -> Self {
        let cobs = Cobs::<N>::new();
        Self { cobs }
    }

    fn encode_u8(&mut self, value: u8) {
        unsafe {
            postcard_cobs_encode_u8(&mut self.cobs.cobs as *mut cobs, value);
        }
    }

    fn encode_u16(&mut self, value: u16) {
        unsafe {
            postcard_cobs_encode_u16(&mut self.cobs.cobs as *mut cobs, value);
        }
    }
}

#[cfg(test)]
mod test {
    use std::ops::DerefMut;

    use crate::{postcard_cobs::PostcardCobs, Cobs};

    #[test]
    fn encoding() {
        // buffer to store data
        let mut encoder = PostcardCobs::<256>::new();
        encoder.cobs.start_frame();
        encoder.encode_u8(56);
        encoder.cobs.end_frame();

        dbg!(postcard::from_bytes_cobs::<u8>(
            &mut encoder.cobs.buf.deref_mut().as_mut_slice()[1..]
        ));
    }
}
