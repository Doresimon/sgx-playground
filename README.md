# sgx-playground

learn to write sgx app~

## Project Structure

In an Intel SGX project, you should normally prepare the following files:

1. `.edl` - Enclave Definition Language file.
2. `.ecf` - Enclave Configuration File.
3. `.key` - Signing key files
4. `.c .cpp .h ...` - App and Enclave source code
5. `makefile`
   - 使用 Edger8r Tool 生成 edger routines
   - build app 和 enclave
   - 对 enclave 签名
6. `.sh` - Linker script
