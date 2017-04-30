#!groovy

pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                sh '''
                mkdir -p cmake-build-debug/
                cd cmake-build-debug/
                cmake ..
                cmake --build .
                '''
            }
        }
    }
}
