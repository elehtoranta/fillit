# 42 Fillit - Hip to be square
### A program to find a smallest square of given tetris pieces in the least amount of time.

## Usage
1. Clone with `git clone https://github.com/akkrecola/fillit.git fillit`
2. `make` in the repository root. It compiles the *libft* library and binary *fillit*.
3. To run: `./fillit path/to/test/file`.
  - Note: Files with invalid formatting will produce an error.
  - You can use the provided test files in `eval_tests/test_files/valid/`.
#### Example:
  ```
  $ ./fillit eval_tests/test_files/valid/3_reverse
  CCBB
  CAAB
  CAAB
  ....
  $ ./fillit eval_tests/test_files/valid/22_valid
  AABBBBCDD.
  AAEE..C.D.
  ..EFFFC.D.
  H.ELLFCGGG
  HHHILLJG.V
  RIIIMMJVVV
  RRNMMJJPPP
  RONNKTTTPS
  OOQNKTU.SS
  OQQQKKUUUS
  $
  ```
