NAME		=	libftbitmap.a

DEP			= 	ft_bitmap.h Makefile

SOURCES		= 	ft_create_bitmap.c ft_load_bitmap.c ft_save_bitmap.c \
				ft_destroy_bitmap.c ft_bitmap_set_pixel.c \
				ft_create_bitmap_from_data.c \
				ft_bitmap_get_pixel_color.c

OBJS		=	$(patsubst %.c, $(BUILD)/%.o, $(SOURCES))

BUILD		=	./build

CC			=	cc

RM			=	rm -rf

CFLAGS		=	-Wall -Wextra -Werror

AR			=	ar rcs

# Colors
RESET  = \033[0m
GREEN  = \033[32m
BLUE   = \033[34m
YELLOW = \033[0;93m

$(BUILD)/%.o:	%.c $(DEP)
				@echo "${BLUE}Compiling $<${RESET}"
				@$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(BUILD) $(OBJS)
				@echo "${GREEN}Building ft_bitmap...${RESET}"
				@$(AR) $(NAME) $(OBJS)
				@echo "${GREEN}Done.${RESET}"

$(BUILD):
			@mkdir $(BUILD)

demo: 		$(NAME)
			@$(CC) $(CFLAGS) test.c -I. -L. -lftbitmap $(NAME) -o test

clean:		
				@echo "${YELLOW}Cleaning build${RESET}"
				@$(RM) $(BUILD)

fclean:
				@echo "${YELLOW}Cleaning Everyting${RESET}"
				@$(RM) $(BUILD)
				@$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all bonus clean fclean re demo