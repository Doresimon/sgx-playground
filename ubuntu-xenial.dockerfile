# docker build . -f ./ubuntu-xenial.dockerfile -t u16
# docker run -it -v /Users/guanjixing/Desktop/git/github/Doresimon/sgx-playground:/home/dev u16


# OR
# docker run -dit -v /Users/guanjixing/Desktop/git/github/Doresimon:/home/dev u16 
# docker exec -it test /bin/bash


# docker run -d --name test-sgx tozd/sgx:ubuntu-xenial
# docker exec -t -i test-sgx bash


FROM tozd/sgx:ubuntu-xenial

RUN rm /bin/sh && ln -s /bin/bash /bin/sh

RUN apt-get update && apt-get install -y locales && rm -rf /var/lib/apt/lists/* \
    && localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8
ENV LANG en_US.utf8

RUN mkdir /home/dev

WORKDIR /home/dev

RUN source /opt/intel/sgxsdk/environment

ENV SGX_MODE SIM
ENV SGX_SDK /opt/intel/sgxsdk
ENV PATH $PATH:$SGX_SDK/bin:$SGX_SDK/bin/x64
ENV PKG_CONFIG_PATH $PKG_CONFIG_PATH:$SGX_SDK/pkgconfig
ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SGX_SDK/sdk_libs

# export SGX_SDK=/opt/intel/sgxsdk
# export PATH=$PATH:$SGX_SDK/bin:$SGX_SDK/bin/x64
# export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$SGX_SDK/pkgconfig
# if [ -z "$LD_LIBRARY_PATH" ]; then
# export LD_LIBRARY_PATH=$SGX_SDK/sdk_libs
# else
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SGX_SDK/sdk_libs
# fi



ENTRYPOINT [ "/bin/bash" ]