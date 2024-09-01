use crate::{
    cobs, postcard_cobs_encode_i16, postcard_cobs_encode_i32, postcard_cobs_encode_i64,
    postcard_cobs_encode_i8, postcard_cobs_encode_u16, postcard_cobs_encode_u32,
    postcard_cobs_encode_u64, postcard_cobs_encode_u8, Cobs,
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

    fn encode_u64(&mut self, value: u64) {
        unsafe {
            postcard_cobs_encode_u64(&mut self.cobs.cobs as *mut cobs, value);
        }
    }

    fn encode_i8(&mut self, value: i8) {
        unsafe { postcard_cobs_encode_i8(&mut self.cobs.cobs as *mut cobs, value) }
    }

    fn encode_i16(&mut self, value: i16) {
        unsafe { postcard_cobs_encode_i16(&mut self.cobs.cobs as *mut cobs, value) }
    }
    fn encode_i32(&mut self, value: i32) {
        unsafe { postcard_cobs_encode_i32(&mut self.cobs.cobs as *mut cobs, value) }
    }
    fn encode_i64(&mut self, value: i64) {
        unsafe { postcard_cobs_encode_i64(&mut self.cobs.cobs as *mut cobs, value) }
    }
}

#[cfg(test)]
mod test {

    use rand::Rng;

    use crate::postcard_cobs::PostcardCobs;

    #[test]
    fn u8() {
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

    #[test]
    fn u16() {
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

    #[test]
    fn u32() {
        let mut rng = rand::thread_rng();
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

    #[test]
    fn u64() {
        let mut rng = rand::thread_rng();
        let mut encoder = PostcardCobs::<256>::new();
        for i in 0..1000000 {
            let value = rng.gen();
            encoder.cobs.start_frame();
            encoder.encode_u64(value);
            encoder.cobs.end_frame();
            assert_eq!(
                postcard::from_bytes_cobs::<u64>(&mut encoder.buffer())
                    .unwrap_or_else(|_| panic!("value {value}")),
                value
            );
            encoder.cobs.reset();
        }
    }

    #[test]
    fn i8() {
        let mut encoder = PostcardCobs::<256>::new();
        for value in i8::MIN..i8::MAX {
            encoder.cobs.start_frame();
            encoder.encode_i8(value);
            encoder.cobs.end_frame();
            assert_eq!(
                postcard::from_bytes_cobs::<i8>(&mut encoder.buffer()).unwrap(),
                value
            );
            encoder.cobs.reset();
        }
    }

    #[test]
    fn i16() {
        let mut encoder = PostcardCobs::<256>::new();
        for value in i16::MIN..i16::MAX {
            encoder.cobs.start_frame();
            encoder.encode_i16(value);
            encoder.cobs.end_frame();
            assert_eq!(
                postcard::from_bytes_cobs::<i16>(&mut encoder.buffer()).unwrap(),
                value
            );
            encoder.cobs.reset();
        }
    }

    #[test]
    fn i32() {
        let mut encoder = PostcardCobs::<256>::new();
        let mut rng = rand::thread_rng();
        for i in 0..1000000 {
            let value = rng.gen();
            encoder.cobs.start_frame();
            encoder.encode_i32(value);
            encoder.cobs.end_frame();
            assert_eq!(
                postcard::from_bytes_cobs::<i32>(&mut encoder.buffer()).unwrap(),
                value
            );
            encoder.cobs.reset();
        }
    }

    #[test]
    fn i64() {
        let mut encoder = PostcardCobs::<256>::new();
        let mut rng = rand::thread_rng();
        for i in 0..1000000 {
            let value = rng.gen();
            encoder.cobs.start_frame();
            encoder.encode_i64(value);
            encoder.cobs.end_frame();
            assert_eq!(
                postcard::from_bytes_cobs::<i64>(&mut encoder.buffer()).unwrap(),
                value
            );
            encoder.cobs.reset();
        }
    }
}
