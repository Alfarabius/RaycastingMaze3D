LIBFT_PATH	=	./Libft
MLX_PATH	=	./minilibx_mms_20200219
MLX_LINUX_PATH	=	./minilibx-linux
SRCS_PATH	=	./srcs
OBJS_PATH	=	./objs
INC_PATH	=	./inc

SRCS	=	calc_line.c \
			draw_sprites.c \
			input.c \
			parse_color.c \
			parser.c \
			cube_init.c \
			erorr_handler.c \
			loop_processor.c \
			parse_player.c \
			screenshot.c \
			draw_img.c \
			get_next_line.c \
			main.c \
			parse_resolution.c \
			draw_line.c \
			get_next_line_utils.c \
			map.c \
			parse_sprite.c \
			utils.c \
			create_map.c

HEAD	=	$(INC_PATH)/cub.h
OBJS	=	$(addprefix $(OBJS_PATH)/, $(SRCS:.c=.o))
NAME	=	cub3D
LIBFT	=	$(LIBFT_PATH)/libft.a
MLX	=	-lmlx
OPENGL	=	-framework OpenGL
APPKIT	=	-framework AppKit
DYLIB	=	libmlx.dylib
CC	=	gcc
CFLAGS	=	-Wall -Wextra
INC	=	-I $(INC_PATH)
RM	=	rm -f
RM_DIR	=	rm -rf

.PHONY: all init clean fclean re screenshot start test norm

all:	init $(NAME)

$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%.c $(HEAD)
	@ echo "compile $@"
	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@ -g

$(NAME):	$(HEAD)	$(OBJS) $(LIBFT)
	@ $(CC) $(CFLAGS) -O2 -o $@ $(INC) $(OBJS) $(LIBFT) $(DYLIB) -L $(MLX_PATH) $(MLX) $(OPENGL) $(APPKIT)

linux: linux_init linux_name
	@ echo "compile for $@"

linux_init:
	@ mkdir -p $(OBJS_PATH)
	@ make -C $(LIBFT_PATH)
	@ make -C $(MLX_LINUX_PATH)

linux_name:	$(HEAD) $(OBJS) $(LIBFT)
	@ $(CC) -O2 -o $(NAME) $(OBJ) -L $(MLX_LINUX_PATH) -lmlx -lm -lbsd -lX11 -lXext

init:
	@ mkdir -p $(OBJS_PATH)
	@ make -C $(LIBFT_PATH)
	@ make -C $(MLX_PATH)
	@ cp $(MLX_PATH)/$(DYLIB) ./

test: re ./configs/msp.cub
	@ ./cub3D ./configs/msp.cub

start: re ./configs/con.cub
	@ ./cub3D ./configs/con.cub

screenshot: re ./configs/con.cub
	@ ./cub3d ./configs/con.cub --save

norm:
	@ norminette $(addprefix $(SRCS_PATH)/, $(SRCS)) $(HEAD)
	@ make norm -C $(LIBFT_PATH)

clean:
	@ $(RM) $(OBJS)
	@ $(RM_DIR) $(OBJS_PATH)
	@ make -C $(LIBFT_PATH) clean
	@ make -C $(MLX_PATH) clean

fclean: clean
	@ $(RM) $(NAME) screenshot.bmp $(DYLIB)
	@ make -C $(LIBFT_PATH) fclean

re: fclean all
