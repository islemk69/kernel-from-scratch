DOCKER_COMPOSE = docker compose
SERVICE_NAME   = builder

all:
	$(DOCKER_COMPOSE) up -d
	$(DOCKER_COMPOSE) exec $(SERVICE_NAME) make -C src

clean:
	$(DOCKER_COMPOSE) exec $(SERVICE_NAME) make -C src clean

fclean:
	$(DOCKER_COMPOSE) exec $(SERVICE_NAME) make -C src fclean
	$(DOCKER_COMPOSE) down

re: fclean all

.PHONY: all clean fclean re
