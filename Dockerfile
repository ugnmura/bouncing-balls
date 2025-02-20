FROM alpine:latest AS builder
RUN apk add --no-cache gcc musl-dev make
WORKDIR /app
COPY . .
RUN make


FROM alpine:latest
WORKDIR /app
COPY --from=builder /app/ball.out /app/ball.out
EXPOSE 8013
CMD ["./ball.out"]
