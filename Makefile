# Compiler and flags
CXX = g++
CXXFLAGS = -O2
SRC = main_narrow.cpp class_punisher.cpp

# Output directories
OUT_DIR = 1214_Four
OUT_DIR2 = 0210_T1big
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
0210t1_%: $(SRC) #[0210] Same shit in the same day
	$(CXX) $(CXXFLAGS) $^ -DTASK1 $(FLAGS_$*) -o $@

T1_1200_rep: $(addprefix 0224t1_, rand_1200 patch_1200 mute_1200)
#Just follow the add prefix, it will do the following shits. [024]
0224t1_%: $(SRC) #[0224]
	$(CXX) $(CXXFLAGS) $^ -DTASK1 -DREPEAT $(FLAGS_$*) -o $@
#Command for this one would be:
#mkdir 0224_1200_rep
#mkdir 0224_1200_rep/T1_1200_rand  0224_1200_rep/T1_1200_patch 0224_1200_rep/T1_1200_mutate
#mkdir 0224_1200_rep/T1_1200_rand/M1 0224_1200_rep/T1_1200_rand/M2 & mkdir 0224_1200_rep/T1_1200_patch/M1 0224_1200_rep/T1_1200_patch/M2 &mkdir 0224_1200_rep/T1_1200_mutate/M1 0224_1200_rep/T1_1200_mutate/M2 
# ./../../0224t1_rand_1200 & (sleep 1 && ./../../0224t1_rand_1200) & (sleep 2 && ./../../0224t1_rand_1200) & (sleep 3 && ./../../0224t1_rand_1200)
# ./../../0224t1_patch_1200 & (sleep 1 && ./../../0224t1_patch_1200) & (sleep 2 && ./../../0224t1_patch_1200) & (sleep 3 && ./../../0224t1_patch_1200)
# ./../../0224t1_mute_1200 & (sleep 1 && ./../../0224t1_mute_1200) & (sleep 2 && ./../../0224t1_mute_1200) & (sleep 3 && ./../../0224t1_mute_1200)


FLAGS_rand_600 = -DBIGGRID
FLAGS_patch_600 = -DBIGGRID -DPATENT
FLAGS_mute_600 = -DBIGGRID -DMUTATE

T1_600_rep: $(addprefix 0217t1_, rand_600 patch_600 mute_600)
#Just follow the add prefix, it will do the following shits. [0210]
0217t1_%: $(SRC) #[0210] Same shit in the same day
	$(CXX) $(CXXFLAGS) $^ -DTASK1 -DREPEAT $(FLAGS_$*) -o $@

#0218 smaller but longer
T1_200_rep: $(addprefix 0218t1_, rand_200 patch_200 mute_200)
0218t1_%: $(SRC) #[0210] Same shit in the same day
	$(CXX) $(CXXFLAGS) $^ -DTASK1 -DREPEAT $(FLAGS_$*) -o $@


0103t1_%: $(SRC)
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

move2:
	@echo "Moving..."

	$(foreach dir, T1_1200_rand T1_1200_patch T1_1200_mutate, \
		mv 0224_1200_rep/$(dir)/*mod_00.dat 0224_1200_rep/$(dir)/M1 ; \
		mv 0224_1200_rep/$(dir)/*mod_01.dat 0224_1200_rep/$(dir)/M2 ; \
	)



generate_pics:
	@echo "Generate_pics..."
	mkdir -p $(FINAL_DIR)
	$(foreach dir, T1_200_rand T1_800_rand T1_200_patch T1_800_patch T1_200_mutate T1_800_mutate T2_200_rand T2_800_rand T2_200_patch T2_800_patch T2_200_mutate T2_800_mutate, \
		$(foreach mode, M1 M2, \
			python3 cat_b.py $(OUT_DIR)/$(dir)/$(mode) $(FINAL_DIR)/1214_$(subst _,,$(dir))_$(mode).tex ; \
		) \
	)

gen_pics_big:
	@echo "Generate_pics..."
	mkdir -p $(FINAL_DIR)
	$(foreach dir, T1_1200_rand  T1_1200_patch T1_1200_mutate  T2_1200_rand  T2_1200_patch T2_1200_mutate, \
		$(foreach mode, M1 M2, \
			python3 cat_b.py $(OUT_DIR2)/$(dir)/$(mode) $(FINAL_DIR)/0210_$(subst _,,$(dir))_$(mode).tex ; \
		) \
	)
#1210 Ok, I replicate a new one



#0218, this is for the repeating one
OUT_DIR3 = 0218_T1
gen_pics_rep200:
	@echo "Generate_pics..."
	mkdir -p $(FINAL_DIR)
	$(foreach dir, T1_200_rand  T1_200_patch T1_200_mutate, \
		$(foreach mode, M1 M2, \
			python3 cat_b.py $(OUT_DIR3)/$(dir)/$(mode) $(FINAL_DIR)/$(subst _,,$(dir))_$(mode)_rep.tex ; \
		) \
	)


#0218, this is for the repeating one
OUT_DIR4 = 0224_1200_rep
gen_pics_rep200:
	@echo "Generate_pics..."
	mkdir -p $(FINAL_DIR)
	$(foreach dir, T1_1200_rand  T1_1200_patch T1_1200_mutate, \
		$(foreach mode, M1 M2, \
			python3 cat_b.py $(OUT_DIR4)/$(dir)/$(mode) $(FINAL_DIR)/$(subst _,,$(dir))_$(mode)_rep.tex ; \
		) \
	)


clean:
	@echo "Cleaning up..."
	rm -f 0103t*_patch_* 0103t*_rand_* 0103t*_mute_* 0210t* 0218t* 0224t1*

clean2:
	@echo "Cleaning up..."
	rm -f $(OUT_DIR)/T1_*/M*/* $(OUT_DIR)/T2_*/M*/*