DOCKER_COMPOSE = docker compose
SERVICE_NAME   = builder

all:
	$(DOCKER_COMPOSE) up

iso: all

clean:
	make -C src clean

fclean:
	make -C src fclean

re: fclean all

.PHONY: all clean fclean re