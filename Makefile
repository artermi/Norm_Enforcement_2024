# Compiler and flags
CXX = g++
CXXFLAGS = -O2
SRC = main_narrow.cpp class_punisher.cpp

# Output directories
OUT_DIR = 1214_Four
FINAL_DIR = 1214_T1T2_Final

# Flags
FLAGS_rand_200 =
FLAGS_rand_800 = -DBIGGRID
FLAGS_patch_200 = -DPATENT
FLAGS_patch_800 = -DBIGGRID -DPATENT
FLAGS_mute_200 = -DMUTATE
FLAGS_mute_800 = -DBIGGRID -DMUTATE
FLAGS_T3_rand = -DT3

# Targets
all: T1 T2

T1: $(addprefix 0103t1_, rand_200 rand_800 patch_200 patch_800 mute_200 mute_800)

T2: $(addprefix 0103t2_, rand_200 rand_800 patch_200 patch_800 mute_200 mute_800)

T3_rand:
	$(CXX) $(CXXFLAGS) class_punisher.cpp T3_rand_0205.cpp $(FLAGS_T3_rand) -o t3rand0205
#0205 use T3 rand


#This shit is for the bigger thing requested [0210]
FLAGS_rand_1200 = -DBIGGRID
FLAGS_patch_1200 = -DBIGGRID -DPATENT
FLAGS_mute_1200 = -DBIGGRID -DMUTATE


T1_1200: $(addprefix 0210t1_, rand_1200 patch_1200 mute_1200)
#Just follow the add prefix, it will do the following shits. [0210]

0103t1_%: $(SRC)
	$(CXX) $(CXXFLAGS) $^ -DTASK1 $(FLAGS_$*) -o $@

0210t1_%: $(SRC) #[0210] Same shit in the same day
	$(CXX) $(CXXFLAGS) $^ -DTASK1 $(FLAGS_$*) -o $@

0103t2_%: $(SRC)
	$(CXX) $(CXXFLAGS) $^ $(FLAGS_$*) -o $@



move:
	@echo "Moving..."

	$(foreach dir, T1_200_mutate T1_800_mutate T1_200_patch T1_800_patch T1_200_rand T1_800_rand T2_200_mutate T2_800_mutate T2_200_patch T2_800_patch T2_200_rand T2_800_rand, \
		$(foreach mode, mod_00 mod_01, \
			mv $(OUT_DIR)/$(dir)/*$(mode).dat $(OUT_DIR)/$(dir)/M$(subst mod_0,,$(mode)) ; \
		) \
	)


generate_pics:
	@echo "Generate_pics..."
	mkdir -p $(FINAL_DIR)
	$(foreach dir, T1_200_rand T1_800_rand T1_200_patch T1_800_patch T1_200_mutate T1_800_mutate T2_200_rand T2_800_rand T2_200_patch T2_800_patch T2_200_mutate T2_800_mutate, \
		$(foreach mode, M1 M2, \
			python3 cat_b.py $(OUT_DIR)/$(dir)/$(mode) $(FINAL_DIR)/1214_$(subst _,,$(dir))_$(mode).tex ; \
		) \
	)

clean:
	@echo "Cleaning up..."
	rm -f 0103t*_patch_* 0103t*_rand_* 0103t*_mute_* 0210t*

clean2:
	@echo "Cleaning up..."
	rm -f $(OUT_DIR)/T1_*/M*/* $(OUT_DIR)/T2_*/M*/*