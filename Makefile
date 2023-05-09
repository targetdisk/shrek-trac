UNAME=$(shell uname)
GOLLUM ?= gollum
GITREF ?= main
ifeq ($(UNAME),Linux)
	OPEN=xdg-open
endif
ifeq ($(detected_OS),Darwin)
	OPEN=open
endif

pub-css:
	-[ ! -e pub.css ] && wget https://github.com/manuelp/pandoc-stylesheet/raw/acac36b976966f76544176161ba826d519b6f40c/pub.css

README: pub-css # Requires Pandoc to be installed
	pandoc README.md -s -c pub.css -o README.html
	$(OPEN) README.html

blockifiers: commentifier.c
	$(CC) -Wall $< -o commentifier
	$(CC) -Wall -DCODIFIER $< -o codifier
	$(CC) -Wall -DDOS_CODIFIER $< -o dos_codifier
	$(CC) -Wall -DINLINE_CODIFIER $< -o inline_codifier

test:
	$(GOLLUM) --config config.rb --ref $(GITREF)
