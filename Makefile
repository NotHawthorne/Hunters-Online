NAME = hunters
CC := g++

all: $(NAME)

MODULES := src/window src/client includes
LIBDIRS := 
LIBS := -lncurses -lform -lpthread -lsqlite3
#CXXFLAGS := -Iincludes -Wall -Werror -Wextra -g
CXXFLAGS := -Iincludes -g #-fsanitize=address
MODNAME := module.mk
SRC :=

include $(patsubst %,%/$(MODNAME),$(MODULES))

OBJ :=  $(patsubst %.cpp,%.o,$(filter %.cpp,$(SRC)))
DEP :=	$(patsubst %.cpp,%.d,$(filter %.cpp,$(SRC)))

-include $(DEP)

$(NAME): $(OBJ)
	@$(CC) $(CXXFLAGS) $(OBJ) $(LIBS) -o $@

%.d : %.c
	@./depend.sh $*.o $(CXXFLAGS) $< > $@
	@printf '\t%s' "$(CC) $(CXXFLAGS) -c -o $*.o $<" >> $@
	@echo $@ >> all.log

clean:
	rm -f $(OBJ)
	rm -f $(shell cat all.log)
	@rm -f all.log

clean_nolib:
	rm -f $(OBJ)
	rm -f $(shell cat all.log)
	@rm -f all.log

fclean: clean_nolib
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
