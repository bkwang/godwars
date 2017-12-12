CC      := gcc
C_FLAGS := -g -Wall -Wall
L_FLAGS := -lz -lcrypt -lpthread -lm
O_DIR   := obj

FILES = act_comm act_info act_move act_obj act_wiz comm const \
          db fight handler interp magic save special update \
          kav_wiz kav_fight kav_info clan more \
          home rot_wiz demon werewolf olc string \
          bit core board desc_map changes

.SUFFIXES:

godwars: $(FILES:%=$(O_DIR)/%.o)
	@rm -f godwars
	@echo [`date +%T`] Linking executable ...
	@$(CC) -o godwars $(FILES:%=$(O_DIR)/%.o) $(L_FLAGS)
	@chmod 755 godwars

-include $(FILES:%=$(O_DIR)/%.d)

%.o $(O_DIR)/%.o : %.c
	@echo [`date +%T`] Compiling $< ...
	@$(CC) -c -MMD -MP $(C_FLAGS) $*.c -o $(O_DIR)/$*.o

clean:
	@echo [`date +%T`] Cleaning code...
	@rm -f $(O_DIR)/*.o
	@rm -f $(O_DIR)/*.d
	@rm -f *.*~

distclean:
	@echo [`date +%T`] Cleaning code...
	@rm -f $(O_DIR)/*.o
	@rm -f $(O_DIR)/*.d
	@rm -f *.*~
	@rm -f godwars

