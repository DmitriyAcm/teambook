PDFLATEX=pdflatex -shell-escape

all: main.pdf

main.pdf: main.tex
	$(PDFLATEX) main
	$(PDFLATEX) main
	$(PDFLATEX) main
	rm -f *.{aux,log,toc,fls,fdb_latexmk}
	rm -rf _code/
	rm -rf _minted-main

clean:
	rm main.pdf
	rm -f *.{aux,log,toc,fls,fdb_latexmk}
	rm -rf _code/
	rm -rf _minted-main
