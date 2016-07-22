# DetecteurViolaJones
C++ project implementing a Viola-Jones face detector.

**Keywords**: Viola-Jones, face recognition, Haar features, AdaBoost, classifiers.

## Introduction
The objective of this project is to implement a Viola-Jones face recognition system.  
We have used the open library `CImg` to load the images. At the end we have implemented a
strong classifier used to distinguish faces and non-faces. The results and the report can be found in the Rapport directory (in French)
and the C++ files in the Scripts directory.

## How to
Note: [ImageMagick](http://www.imagemagick.org/script/install-source.php) package required in order to use the `CImg` library.  
Clone the github repository and run one of the following commands:

	make test_q_1_1 # test the integral image
	make testEps # test for epsilon and K (see report)
	make main # test the viola-jones algorithm
	make clean # clean extra files

##References
[1] Yoav Freund and Robert E. Schapire. A decision-theoretic generalization of on-line learning and an application to boosting. 1997.

[2] Frank Rosenblatt. The perceptron: A probabilistic model for information storage and organization in the brain. In Psychological Review, volume 65, pages 386–408, 1958.

[3] Paul Viola and Michael Jones. Robust real-time object detection. In International Journal of Computer Vision, 2001.
