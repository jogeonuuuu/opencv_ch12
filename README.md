# opencv_ch12
### 실습과제 1번
- labelex.png 영상파일(컬러영상)에서 레이블링을 수행하고 객체의 면적이 최대, 최소인 객체를 찾고 아래처럼 콘솔창에 정보를 출력하고 원본영상에 바운딩 박스를 그려주시오.
- 힌트 : 컬러->그레이->이진화(반전)->레이블링
<실행결과>
![image](https://github.com/jogeonuuuu/opencv_ch12/assets/169337989/50805fd2-9203-49ca-8b6d-a631515456a4)

### 실습과제 2번
- polygon.bmp 영상파일에서 레이블링을 수행하고 다음 처럼 콘솔창에 아래와 같은 정보를 출력하고 영상원본에 바운딩 박스와 레이블값을 그려주는 코드를 작성하시오. color는 무게중심 좌표에서 원본 영상의 컬러를 출력할 것
<실행결과>
![image](https://github.com/jogeonuuuu/opencv_ch12/assets/169337989/a6b8ed76-47d6-455c-a042-801faa4c536b)
![image](https://github.com/jogeonuuuu/opencv_ch12/assets/169337989/1a069208-4c1a-404e-8c3a-056cb24b3098)

### 실습과제 3번
- polygon.bmp 영상 파일에서 레이블링을 수행하고 각 객체의 무게중심을 직접 계산하여 아래 처럼 화면에 출력하시오.
- 레이블링 함수의 결과와 같은지 비교하시오.
- 무게중심 x좌표 = (객체영역에 포함된 모든점의 x좌표의 합) / 객체영역의 총픽셀수
- 무게중심 y좌표 = (객체영역에 포함된 모든점의 y좌표의 합) / 객체영역의 총픽셀수
<실행결과>
![image](https://github.com/jogeonuuuu/opencv_ch12/assets/169337989/1e059206-d09a-4bd6-ae5b-f558a11de451)

### 실습과제 4번
- 11장-2의 실습과제4의 결과를 이용하여 자동차의 번호판 영역을 검출하여 다음처럼 빨간색으로 표시하라.
<실행결과>
![image](https://github.com/jogeonuuuu/opencv_ch12/assets/169337989/d54ba4da-a279-4a23-94bf-6368974cc8c5)
