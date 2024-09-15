# Changelog

## 1.0.0 (2024-09-15)


### Features

* basic postcard decode functions ([ae58683](https://github.com/dw-labs-org/postcard-c/commit/ae58683008183e1879c5ba210ffdd5a78c61c894))
* check for leading zero ([5651412](https://github.com/dw-labs-org/postcard-c/commit/5651412e9c54d292f0d24dcb561ffe57ca7d9366))
* cobs decoder check for zero ([1ad601c](https://github.com/dw-labs-org/postcard-c/commit/1ad601c0f9d588b620c520e7fa9a1f5e9cb2883d))
* cobs decoder place bytes function ([ff4ada6](https://github.com/dw-labs-org/postcard-c/commit/ff4ada6fbc46d5106caf61db7796b8d391042cc6))
* cobs decoder reset functions ([54845b3](https://github.com/dw-labs-org/postcard-c/commit/54845b384661184f3560bb3bfac906e44dd0d390))
* cobs encode function ([e0e0f1c](https://github.com/dw-labs-org/postcard-c/commit/e0e0f1c6ee713e994631dcb408e0958f18d53173))
* cobs encoder helper functions ([9d68632](https://github.com/dw-labs-org/postcard-c/commit/9d6863211e0119863f123559ff211a5423ad5eb1))
* cobs error codes ([fe2653d](https://github.com/dw-labs-org/postcard-c/commit/fe2653d94ca2a12a2893b9f344cc24b1835c15bf))
* cobs partial decoding ([63fc4bd](https://github.com/dw-labs-org/postcard-c/commit/63fc4bdddc17310c49757b6eae5628595d18c661))
* cobs unchecked write ([7c1edcd](https://github.com/dw-labs-org/postcard-c/commit/7c1edcd6a06cd325b8be0484f3ff49c2848a731b))
* cobs_decoder frame pending ([41c3315](https://github.com/dw-labs-org/postcard-c/commit/41c3315301dbd6bdf76f197d339103e95417949e))
* cobs_encoder direct write frame ([8159437](https://github.com/dw-labs-org/postcard-c/commit/8159437bd16fd69422ad29239f42e656bc34987a))
* decode function return length. ([2c76cb7](https://github.com/dw-labs-org/postcard-c/commit/2c76cb7f49fbd0a27ede4b0a287ff78a925b5cf3))
* direct write to decode buffer ([e69297e](https://github.com/dw-labs-org/postcard-c/commit/e69297ec44078f495ea7c6a0d266d66dc2ab7458))
* encode byte_array ([d745bd7](https://github.com/dw-labs-org/postcard-c/commit/d745bd7fafd988f316078207a50fcd30702108d1))
* fast in place short decoding ([871f38c](https://github.com/dw-labs-org/postcard-c/commit/871f38cc8b1ec2799f4060c756269a40e3d6119f))
* fast multi byte cobs ([5322796](https://github.com/dw-labs-org/postcard-c/commit/5322796711186b895b25016e4180198a91e23293))
* partial decode resume ([d1d478b](https://github.com/dw-labs-org/postcard-c/commit/d1d478ba4ff698caebde376fe0f98aac19dae979))
* postcard cobs encode discriminant ([31aaa31](https://github.com/dw-labs-org/postcard-c/commit/31aaa311c9493277ba4bd987e2d5b3d6927de83e))
* postcard decode returns length ([96683b5](https://github.com/dw-labs-org/postcard-c/commit/96683b5adb25c59f1014e6630ed226099570a2e1))
* postcard increments buffer ([bee539d](https://github.com/dw-labs-org/postcard-c/commit/bee539d089eb257bb5ce2aa7d0cbc947aaf8cf1f))
* sequential circular decode ([1251049](https://github.com/dw-labs-org/postcard-c/commit/12510490ce030148f0b19bf0793a12173b6e2b40))
* u64 and i64 encoding ([51126b0](https://github.com/dw-labs-org/postcard-c/commit/51126b059d6b9d1ff6f7c5a2d384d90c75e30cfc))
* working cobs encoder ([6c118b6](https://github.com/dw-labs-org/postcard-c/commit/6c118b6aa498ed62c35c7b3fb843483d4a2c6a33))


### Bug Fixes

* buf increment ([b19762d](https://github.com/dw-labs-org/postcard-c/commit/b19762d3468c6dae9bb94b9dba9b14577166017e))
* cobs decode with overhead byte ([85561e8](https://github.com/dw-labs-org/postcard-c/commit/85561e86d3e3b5919b7ac950bc8f4c78b3c55cab))
* cobs encoding no leading zero ([7d73ff8](https://github.com/dw-labs-org/postcard-c/commit/7d73ff8c66c5e1b79e3f004e1d7b81ed51362199))
* decode test ([409ac74](https://github.com/dw-labs-org/postcard-c/commit/409ac749ffdab7b202d68211b0cc3c943cad7102))
* frame start off by 1 ([99f6ea6](https://github.com/dw-labs-org/postcard-c/commit/99f6ea670128c7091ef2e35568bb5ce727783c0f))
* hopefully shift fix... ([2c8c227](https://github.com/dw-labs-org/postcard-c/commit/2c8c22746dad84d876311ff5cde2a13b3f85a73c))
* overhead byte decoding issue ([2ab8a0b](https://github.com/dw-labs-org/postcard-c/commit/2ab8a0b7f44213ba82cfd49e1e9c54abed4a8135))
* postcard cobs u16 and u32 encoding ([77e9504](https://github.com/dw-labs-org/postcard-c/commit/77e950474d819fb8a0fb94035947434febc84e82))
