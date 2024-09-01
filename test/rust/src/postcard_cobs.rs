use crate::{
    cobs, postcard_cobs_encode_u16, postcard_cobs_encode_u32, postcard_cobs_encode_u8, Cobs,
};

struct PostcardCobs<const N: usize> {
    pub cobs: Cobs<N>,
}

impl<const N: usize> PostcardCobs<N> {
    fn new() -> Self {
        let cobs = Cobs::<N>::new();
        Self { cobs }
    }

    fn buffer(&self) -> Vec<u8> {
        self.cobs
            .buf
            .iter()
            .copied()
            .take_while(|b| *b != 0)
            .collect()
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

    fn encode_u32(&mut self, value: u32) {
        unsafe {
            postcard_cobs_encode_u32(&mut self.cobs.cobs as *mut cobs, value);
        }
    }
}

#[cfg(test)]
mod test {
    use std::ops::DerefMut;

    use rand::Rng;

    use crate::{postcard_cobs::PostcardCobs, Cobs};

    /// Check encoding of u8s
    #[test]
    fn u8() {
        // buffer to store data
        let mut encoder = PostcardCobs::<256>::new();
        for value in 0u8..255 {
            encoder.cobs.start_frame();
            encoder.encode_u8(value);
            encoder.cobs.end_frame();
            assert_eq!(
                postcard::from_bytes_cobs::<u8>(&mut encoder.buffer()).unwrap(),
                value
            );
            encoder.cobs.reset();
        }
    }

    /// Check encoding of u16s
    #[test]
    fn u16() {
        // buffer to store data
        let mut encoder = PostcardCobs::<256>::new();
        for value in 0u16..u16::MAX {
            encoder.cobs.start_frame();
            encoder.encode_u16(value);
            encoder.cobs.end_frame();
            assert_eq!(
                postcard::from_bytes_cobs::<u16>(&mut encoder.buffer()).unwrap(),
                value
            );
            encoder.cobs.reset();
        }
    }

    /// Check encoding of u32s
    #[test]
    fn u32() {
        let mut rng = rand::thread_rng();
        // buffer to store data
        let mut encoder = PostcardCobs::<256>::new();
        for i in 0..1000000 {
            let value = rng.gen();
            encoder.cobs.start_frame();
            encoder.encode_u32(value);
            encoder.cobs.end_frame();
            assert_eq!(
                postcard::from_bytes_cobs::<u32>(&mut encoder.buffer())
                    .unwrap_or_else(|_| panic!("value {value}")),
                value
            );
            encoder.cobs.reset();
        }
    }
}
