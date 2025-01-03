all: T1 T2

T1:
	g++ -O main_narrow.cpp class_punisher.cpp -DTASK1 -o 0103t1_rand_200
	g++ -O main_narrow.cpp class_punisher.cpp -DTASK1 -DBIGGRID -o 0103t1_rand_600
	g++ -O main_narrow.cpp class_punisher.cpp -DTASK1 -DPATENT -o 0103t1_patch_200
	g++ -O main_narrow.cpp class_punisher.cpp -DTASK1 -DBIGGRID -DPATENT -o 0103t1_patch_600
	g++ -O main_narrow.cpp class_punisher.cpp -DTASK1 -DMUTATE -o 0103t1_mute_200
	g++ -O main_narrow.cpp class_punisher.cpp -DTASK1 -DBIGGRID -DMUTATE -o 0103t1_mute_600

T2:
	g++ -O main_narrow.cpp class_punisher.cpp -o 0103t2_rand_200
	g++ -O main_narrow.cpp class_punisher.cpp -DBIGGRID -o 0103t2_rand_600
	g++ -O main_narrow.cpp class_punisher.cpp -DPATENT -o 0103t2_patch_200
	g++ -O main_narrow.cpp class_punisher.cpp -DBIGGRID -DPATENT -o 0103t2_patch_600
	g++ -O main_narrow.cpp class_punisher.cpp -DMUTATE -o 0103t2_mute_200
	g++ -O main_narrow.cpp class_punisher.cpp -DBIGGRID -DMUTATE -o 0103t2_mute_600


move:
	@echo "Moving..."
	mv 1214_Four/T1_200_mutate/*mode_00.dat 1214_Four/T1_200_mutate/M1
	mv 1214_Four/T1_200_mutate/*mode_01.dat 1214_Four/T1_200_mutate/M2
	mv 1214_Four/T1_600_mutate/*mode_00.dat 1214_Four/T1_600_mutate/M1
	mv 1214_Four/T1_600_mutate/*mode_01.dat 1214_Four/T1_600_mutate/M2

	mv 1214_Four/T1_200_patch/*mode_00.dat 1214_Four/T1_200_patch/M1
	mv 1214_Four/T1_200_patch/*mode_01.dat 1214_Four/T1_200_patch/M2
	mv 1214_Four/T1_600_patch/*mode_00.dat 1214_Four/T1_600_patch/M1
	mv 1214_Four/T1_600_patch/*mode_01.dat 1214_Four/T1_600_patch/M2

	mv 1214_Four/T1_200_rand/*mode_00.dat 1214_Four/T1_200_rand/M1
	mv 1214_Four/T1_200_rand/*mode_01.dat 1214_Four/T1_200_rand/M2
	mv 1214_Four/T1_600_rand/*mode_00.dat 1214_Four/T1_600_rand/M1
	mv 1214_Four/T1_600_rand/*mode_01.dat 1214_Four/T1_600_rand/M2


	mv 1214_Four/T2_200_mutate/*mode_00.dat 1214_Four/T2_200_mutate/M1
	mv 1214_Four/T2_200_mutate/*mode_01.dat 1214_Four/T2_200_mutate/M2
	mv 1214_Four/T2_600_mutate/*mode_00.dat 1214_Four/T2_600_mutate/M1
	mv 1214_Four/T2_600_mutate/*mode_01.dat 1214_Four/T2_600_mutate/M2

	mv 1214_Four/T2_200_patch/*mode_00.dat 1214_Four/T2_200_patch/M1
	mv 1214_Four/T2_200_patch/*mode_01.dat 1214_Four/T2_200_patch/M2
	mv 1214_Four/T2_600_patch/*mode_00.dat 1214_Four/T2_600_patch/M1
	mv 1214_Four/T2_600_patch/*mode_01.dat 1214_Four/T2_600_patch/M2

	mv 1214_Four/T2_200_rand/*mode_00.dat 1214_Four/T2_200_rand/M1
	mv 1214_Four/T2_200_rand/*mode_01.dat 1214_Four/T2_200_rand/M2
	mv 1214_Four/T2_600_rand/*mode_00.dat 1214_Four/T2_600_rand/M1
	mv 1214_Four/T2_600_rand/*mode_01.dat 1214_Four/T2_600_rand/M2

generate_pics:
	@echo "Generate_pics..."
	mkdir 1214_T1T2_Final
	python3 cat_b.py 1214_Four/T1_200_rand/M1 1214_T1T2_Final/1214_T1_rand_200_m1.tex
	python3 cat_b.py 1214_Four/T1_200_rand/M2 1214_T1T2_Final/1214_T1_rand_200_m2.tex
	python3 cat_b.py 1214_Four/T1_600_rand/M1 1214_T1T2_Final/1214_T1_rand_600_m1.tex
	python3 cat_b.py 1214_Four/T1_600_rand/M2 1214_T1T2_Final/1214_T1_rand_600_m2.tex

	python3 cat_b.py 1214_Four/T1_200_patch/M1 1214_T1T2_Final/1214_T1_patch_200_m1.tex
	python3 cat_b.py 1214_Four/T1_200_patch/M2 1214_T1T2_Final/1214_T1_patch_200_m2.tex
	python3 cat_b.py 1214_Four/T1_600_patch/M1 1214_T1T2_Final/1214_T1_patch_600_m1.tex
	python3 cat_b.py 1214_Four/T1_600_patch/M2 1214_T1T2_Final/1214_T1_patch_600_m2.tex

	python3 cat_b.py 1214_Four/T1_200_mutate/M1 1214_T1T2_Final/1214_T1_mutate_200_m1.tex
	python3 cat_b.py 1214_Four/T1_200_mutate/M2 1214_T1T2_Final/1214_T1_mutate_200_m2.tex
	python3 cat_b.py 1214_Four/T1_600_mutate/M1 1214_T1T2_Final/1214_T1_mutate_600_m1.tex
	python3 cat_b.py 1214_Four/T1_600_mutate/M2 1214_T1T2_Final/1214_T1_mutate_600_m2.tex

	python3 cat_b.py 1214_Four/T2_200_rand/M1 1214_T1T2_Final/1214_T2_rand_200_m1.tex
	python3 cat_b.py 1214_Four/T2_200_rand/M2 1214_T1T2_Final/1214_T2_rand_200_m2.tex
	python3 cat_b.py 1214_Four/T2_600_rand/M1 1214_T1T2_Final/1214_T2_rand_600_m1.tex
	python3 cat_b.py 1214_Four/T2_600_rand/M2 1214_T1T2_Final/1214_T2_rand_600_m2.tex

	python3 cat_b.py 1214_Four/T2_200_patch/M1 1214_T1T2_Final/1214_T2_patch_200_m1.tex
	python3 cat_b.py 1214_Four/T2_200_patch/M2 1214_T1T2_Final/1214_T2_patch_200_m2.tex
	python3 cat_b.py 1214_Four/T2_600_patch/M1 1214_T1T2_Final/1214_T2_patch_600_m1.tex
	python3 cat_b.py 1214_Four/T2_600_patch/M2 1214_T1T2_Final/1214_T2_patch_600_m2.tex

	python3 cat_b.py 1214_Four/T2_200_mutate/M1 1214_T1T2_Final/1214_T2_mutate_200_m1.tex
	python3 cat_b.py 1214_Four/T2_200_mutate/M2 1214_T1T2_Final/1214_T2_mutate_200_m2.tex
	python3 cat_b.py 1214_Four/T2_600_mutate/M1 1214_T1T2_Final/1214_T2_mutate_600_m1.tex
	python3 cat_b.py 1214_Four/T2_600_mutate/M2 1214_T1T2_Final/1214_T2_mutate_600_m2.tex


clean:
	@echo "Cleaning up..."
	rm 0103t*_patch_* 0103t*_rand_* 0103t*_mute_*

clean2:
	@echo "Cleaning up..."
	rm 1214_Four/T1_*/M*/* 1214_Four/T2_*/M*/* 