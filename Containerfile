FROM alpine

RUN apk add vim gcc musl-dev python3

COPY hello.c /hello.c
