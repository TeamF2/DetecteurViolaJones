# DetecteurViolaJones
Project in C++ where we implement a Viola-Jones face recognition detector
**Keywords**: Viola-Jones, face recognition, Haar features, AdaBoost, classifiers.

## Introduction
The objective of this project is to implement a Viola Jones face recognition system.
For that we have used the open library `CImg` to load the images. At the end we have implemented a 
robust classifier wich is used to distinguish faces and non faces. The results can be found in the directory Rapport (in french)
and the Scripts in C++ in the directory Scripts.

## How to install
Justs clone the github repo. It is required to have [ImageMagik](http://www.imagemagick.org/script/install-source.php) 
installed in order to use the CImg library. To run the codes just do one of:

	make test_q_1_1 # test the integral image
	make testEps # test for epsilon and K (see raport)
	make main # test the viola-jones algorithm
	make clean # clean extra files
##References
[1] Yoav Freund and Robert E. Schapire. A decision-theoretic generalization of on-line learning and an application to boosting. 1997.
[2] Frank Rosenblatt. The perceptron: A probabilistic model for information storage and organi- zation in the brain. In Psychological Review, volume 65, pages 386–408, 1958.
[3] Paul Viola and Michael Jones. Robust real-time object detection. In International Journal of Computer Vision, 2001.