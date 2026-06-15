CC = gcc
CFLAGS = -Wall -Wextra -pthread

SERVER = kvstore
CLIENT = kvclient

SERVER_SRC = src/main.c \
             src/server.c \
             src/datastore.c \
             src/persistence.c

CLIENT_SRC = src/client.c

all: $(SERVER) $(CLIENT)

$(SERVER):
	$(CC) $(CFLAGS) $(SERVER_SRC) -o $(SERVER)

$(CLIENT):
	$(CC) $(CFLAGS) $(CLIENT_SRC) -o $(CLIENT)

clean:
	rm -f $(SERVER) $(CLIENT)

run-server: $(SERVER)
	./$(SERVER)

run-client: $(CLIENT)
	./$(CLIENT)

.PHONY: all clean run-server run-client