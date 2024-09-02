# postcard-c
A serialisation library for the [postcard](https://crates.io/crates/postcard/1.0.10) format written in C. Supports [Cobs](https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing) framing.

## Data types
The library supports the following serde data types:
### Serialising
- bool
- i8, i16, i32, i64
- u8, u16, u32, u64
- f32, f64
- byte array
- unit_variant

The following can be constructed from the primitives supported above:
- option:
  - None: 0u8
  - Some: 1u8 followed by contained type
- newtype_variant:
  - unit_variant followed by contained type
- seq:
  - length as u16|u32|u64 followed by each element in the array
- tuple:
  - each element in order of definition
- tuple_struct
  - tuple
- tuple_variant
  - unit_variant followed by tuple
- map
  - length as u16|u32|u64 followed by each key value pair as a tuple
- struct
  - each element in the order of definition
- struct_variant
  - unit_variant followed by struct

Not yet supported
- i128
- u128
- char
- string

### Deserialising
Nothing yet.

