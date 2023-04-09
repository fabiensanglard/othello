COMP = gcc -g
OPTIONS     = -lm -lX11 -lXpm -L/usr/X11R6/lib


# Option pour linux -L/usr/X11R6/lib
# Option permettant d'afficher des fichiers .xmp -lXpm 


CHEMIN = .

SRC = $(CHEMIN)/src/
LIB = $(CHEMIN)/lib/
INC = $(CHEMIN)/include/
OBJ = othello.o $(LIB)graphlib.o $(LIB)affichage.o $(LIB)plateau.o $(LIB)arbitre.o $(LIB)ia.o $(LIB)var_globale.o $(LIB)save.o $(LIB)historique.o $(LIB)menu.o

$(shell mkdir -p $(LIB))

othello : $(OBJ)
	$(COMP) -o othello $(OBJ)  $(OPTIONS)

othello.o : othello.c
	$(COMP) -o othello.o -c othello.c

$(LIB)graphlib.o : $(SRC)graphlib.c $(INC)graphlib.h
	$(COMP) -o $(LIB)graphlib.o -c $(SRC)graphlib.c

$(LIB)dessin.o : $(INC)graphlib.h $(SRC)dessin.c $(INC)dessin.h
	$(COMP) -o $(LIB)dessin.o -c $(SRC)dessin.c

$(LIB)affichage.o : $(SRC)affichage.c $(INC)affichage.h
	$(COMP) -o $(LIB)affichage.o -c $(SRC)affichage.c

$(LIB)plateau.o : $(SRC)plateau.c $(INC)plateau.h
	$(COMP) -o $(LIB)plateau.o -c $(SRC)plateau.c

$(LIB)arbitre.o : $(SRC)arbitre.c $(INC)arbitre.h
	$(COMP) -o $(LIB)arbitre.o -c $(SRC)arbitre.c

$(LIB)menu.o : $(SRC)menu.c $(INC)menu.h
	$(COMP) -o $(LIB)menu.o -c $(SRC)menu.c

$(LIB)ia.o : $(SRC)ia.c $(INC)ia.h
	$(COMP) -o $(LIB)ia.o -c $(SRC)ia.c

$(LIB)var_globale.o : $(SRC)var_globale.c $(INC)var_globale.h
	$(COMP) -o $(LIB)var_globale.o -c $(SRC)var_globale.c


$(LIB)save.o :$(SRC)save.c $(INC)save.h
	$(COMP) -o $(LIB)save.o -c $(SRC)save.c


$(LIB)historique.o :$(SRC)historique.c $(INC)historique.h
	$(COMP) -o $(LIB)historique.o -c $(SRC)historique.c



clean :	
	$(RM) $(OBJ)
