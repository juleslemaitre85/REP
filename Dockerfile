FROM gcc:15
WORKDIR /app
COPY . .
CMD ["sh","./run.sh"]

