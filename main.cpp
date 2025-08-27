#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    
    CascadeClassifier face_cascade;
    if (!face_cascade.load("/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml")) {
        cerr << "Error: No file Haarcascade" << endl;
        return -1;
    }


    
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Camera cannot open!" << endl;
        return -1;
    }

    cout << "Tekan ESC untuk keluar..." << endl;

    Mat frame, gray;
    vector<Rect> faces;

    while (true) {
        cap >> frame; // Ambil frame dari kamera
        if (frame.empty()) {
            cerr << "Error: Empty Frame!" << endl;
            break;
        }

        
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        equalizeHist(gray, gray);

       
        face_cascade.detectMultiScale(gray, faces, 1.3, 5);

       
        for (size_t i = 0; i < faces.size(); i++) {
            rectangle(frame, faces[i], Scalar(0, 255, 0), 2);

            // Tambahkan label "Wajah Terdeteksi"
            putText(frame, "Face Detected", Point(faces[i].x, faces[i].y - 10),
                    FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
        }

        
        imshow("Deteksi Wajah - OpenCV", frame);

       
        if (waitKey(10) == 27) {
            cout << "Exit Program." << endl;
            break;
        }
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
