#[cfg(test)]
mod test {
    use rand::{thread_rng, Rng};

    use crate::{
        postcard_decode_double, postcard_decode_float, postcard_decode_u16, postcard_decode_u32,
        postcard_decode_u8, postcard_return_POSTCARD_SUCCESS,
    };

    #[test]
    fn decode_u8() {
        let mut buf = [0; 4];
        for value in 0..u8::MAX {
            postcard::to_slice(&value, &mut buf).unwrap();
            let mut decoded = 0u8;
            unsafe {
                assert_eq!(
                    postcard_return_POSTCARD_SUCCESS,
                    postcard_decode_u8(
                        buf.as_mut_ptr(),
                        buf.as_mut_ptr().add(4),
                        &mut decoded as *mut u8,
                    )
                );
            }
            assert_eq!(value, decoded);
        }
    }

    #[test]
    fn decode_u16() {
        let mut buf = [0; 4];
        for value in 0..u16::MAX {
            postcard::to_slice(&value, &mut buf).unwrap();
            let mut decoded = 0u16;
            unsafe {
                assert_eq!(
                    postcard_return_POSTCARD_SUCCESS,
                    postcard_decode_u16(
                        buf.as_mut_ptr(),
                        buf.as_mut_ptr().add(4),
                        &mut decoded as *mut u16,
                    )
                );
            }
            assert_eq!(value, decoded);
        }
    }

    #[test]
    fn decode_u32() {
        let mut rng = thread_rng();
        let mut buf = [0; 8];
        for i in 0..u16::MAX {
            let value: u32 = rng.gen();
            postcard::to_slice(&value, &mut buf).unwrap();
            let mut decoded = 0u32;
            unsafe {
                assert_eq!(
                    postcard_return_POSTCARD_SUCCESS,
                    postcard_decode_u32(
                        buf.as_mut_ptr(),
                        buf.as_mut_ptr().add(8),
                        &mut decoded as *mut u32,
                    )
                );
            }
            assert_eq!(value, decoded);
        }
    }

    #[test]
    fn decode_f32() {
        let mut rng = thread_rng();
        let mut buf = [0; 8];
        for i in 0..u16::MAX {
            let value: f32 = rng.gen();
            postcard::to_slice(&value, &mut buf).unwrap();
            let mut decoded = 0.0f32;
            unsafe {
                assert_eq!(
                    postcard_return_POSTCARD_SUCCESS,
                    postcard_decode_float(
                        buf.as_mut_ptr(),
                        buf.as_mut_ptr().add(8),
                        &mut decoded as *mut f32,
                    )
                );
            }
            assert_eq!(value, decoded);
        }
    }

    #[test]
    fn decode_f64() {
        let mut rng = thread_rng();
        let mut buf = [0; 10];
        for i in 0..u16::MAX {
            let value: f64 = rng.gen();
            postcard::to_slice(&value, &mut buf).unwrap();
            let mut decoded = 0.0f64;
            unsafe {
                assert_eq!(
                    postcard_return_POSTCARD_SUCCESS,
                    postcard_decode_double(
                        buf.as_mut_ptr(),
                        buf.as_mut_ptr().add(8),
                        &mut decoded as *mut f64,
                    )
                );
            }
            assert_eq!(value, decoded);
        }
    }
}
