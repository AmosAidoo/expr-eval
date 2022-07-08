OUTPUT=eval
FILES=main.c tokenizer.c parser.c
eval: $(FILES)
	$(CC) $(FILES) -o $(OUTPUT)