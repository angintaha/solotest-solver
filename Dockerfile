FROM gcc:latest

WORKDIR /usr/src/myapp
COPY . .
RUN make build
CMD ["./bin/main"]