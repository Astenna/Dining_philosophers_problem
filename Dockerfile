FROM alpine
COPY . /BUILD
RUN apk --update add make g++ ncurses ncurses-dev ncurses-libs
WORKDIR /BUILD
RUN make
ENV TERM xterm