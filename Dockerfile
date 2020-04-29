FROM cpp-build-base:0.1.0 AS build
WORKDIR /src/
COPY --chown=root ./ ./
WORKDIR /src/server
RUN make re
EXPOSE 4242
