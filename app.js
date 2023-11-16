const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);
const { Server } = require("socket.io");
const io = new Server(server);
const { Buffer } = require('node:buffer');
const { SerialPort } = require('serialport');



// const port = new SerialPort({
//   path: 'COM5',
//   baudRate: 9600,
// });
//path에 아두이노 연결된 포트, 시리얼통신 9600으로

var brightness = 0;

app.use('/css', express.static(__dirname + '/node_modules/bootstrap/dist/css'));
//부트스트랩

app.get('/', (req, res) => {
  res.sendFile(__dirname +'/public/index.html');
});

app.get('/test', (req, res) => {
  res.sendFile(__dirname +'/public/testPage.html');
});

app.get('/media/:name', (req, res) => {
  var loaction=req.params.name;
  console.log('check');
  res.sendFile(__dirname +'/media/'+loaction);
});
//요청 인자를 통해 동적으로 medai 폴더에서 이미지를 불러서 보내줌.

//해당 프로젝트 루트폴더 + public~~디렉토리
server.listen(8080, () => {
  console.log('listening on *:8080');
});
console.log("Web Server Started go to 'http://localhost:8080' in your Browser.");
//html 파일로 8080포트로 node 서버 열고


io.on('connection', (socket) => {
  //이벤트핸들러 -> 클라이언트와 연결이 확립될시 실행됨
  console.log('연결확인메시지')
  socket.on('led', function (dataone) {
    //또다른 이벤트핸들러 -> 'led'라는 이벤트를 수신하면 실행
                var command = dataone.value;
                console.log(command)
                var buf = new Buffer.alloc(1);
                buf.writeUInt8(command, 0);

                /*
                var buf = Buffer.from(command, 'utf8');
                문자받으려고 시도했던거
                //https://nodejs.org/api/buffer.html#buffers-and-character-encodings
                */
                
                // console.log(buf)


                //temp  port.write(buf);



                //이부분이 실제로 아두이노에 시리얼로 값을 보낸다.
                socket.emit('ledd', {value: brightness});
                //이부분 실행시 모든 호스트가 아닌 접속중 호스트에만 적용된다.
				
        
        });
        
});

let dhtBuffer = '';
//제이슨 짧게 보내도 한번에 못받아서 끊기고 에러나서 팅겨버리는 현상.
// port.on('data',function(datatwo){
//   // var printdata=data.toString('utf8');
//   // //이렇게 받으니까 바이너리 데이터로 온다. utf8로 문자열 변환했음.
//   // console.log("?: ",printdata)
//   // io.sockets.emit('humidity', {value: printdata}); 

//   dhtBuffer += datatwo.toString();
//   //json 전체 안받고 짤라서 받아서 변환하다가 에러가 나는 것 같으니가 버퍼에 뭉쳐놓고
//   console.log(dhtBuffer);
//   if(!dhtBuffer.includes('{'))
//   {
//     const temp=dhtBuffer
//     console.log('다른신호다');
//     console.log(temp);
//     io.sockets.emit('pause', temp);   
//     dhtBuffer='';
    
//   }
//   //해보니까 못해도 {"h" 정도까지는 보내준다. 그게 아닌경우 다른확인메시지를 보낸거라고 판단해서 이런 if else 문을 적었다.
//   else{
//   if (dhtBuffer.includes('}')) {
//     try{
//     const jsonData = JSON.parse(dhtBuffer);
//     const humidity = jsonData.h;
//     const temperature = jsonData.t;
//     console.log(humidity, temperature);
//     io.sockets.emit('humidity', {value: humidity}); 
//     io.sockets.emit('temperature', {value: temperature}); 

//     dhtBuffer = ''; // 공간 초기화
//   } // 제이슨 }로 끝나니까 그때까지 받다가
//   catch(error){
//     console.error('파싱 오류',error);
//     io.sockets.emit('pause', 3);   
//     dhtBuffer='';//예외처리
//   }
// }}

// }


// );


//포트에서 보낸걸 감지할 이벤트리스너.
// port.on('data',function (data){
//   console.log('data:',port.read())
// })