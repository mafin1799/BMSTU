//Заполнение полей
let device = document.getElementById('device');
device.length = 0;
let serial_number = document.getElementById('sn');
serial_number.length = 0;
let sensor1 = document.getElementById('sensor1');
sensor1.length = 0;
let sensor2 = document.getElementById('sensor2');
sensor2.length = 0;
let device_option = document.createElement('option');
device_option.text = 'Прибор';
let serial_number_option = document.createElement('option');
serial_number_option.text = 'С/Н';
let sensor1_option = document.createElement('option');
sensor1_option.text = 'Температура';
let sensor2_option = document.createElement('option');
sensor2_option.text = 'Влажность';
device.add(device_option);
device.selectedIndex = 0;
serial_number.add(serial_number_option);
serial_number.selectedIndex = 0;
sensor1.add(sensor1_option);
sensor1.selectedIndex = 0;
sensor2.add(sensor2_option);
sensor2.selectedIndex = 0;
//Получение данных для парсинга
const url = '/data';
//Создаем Fetch запрос для поучения данных
var plotData = [];
var plotData_e = [];
fetch(url) // обращаемся к адресу на котором лежат наши данные
    .then(
        function(response) {
            if (response.status !== 200) {
                console.warn('Looks like there was a problem. Status Code: ' +
                    response.status);
                return;
            }
            response.json().then(function(data) { //Здесь начинается работа с данными
                var set_time1 = document.getElementById("dt_1"); //отслеживание первого периода
                времени и выгрузка json
                set_time1.onchange = function() {
                    dt_1 = set_time1.value;
                    console.log(dt_1)
                    var set_time2 = document.getElementById("dt_2"); //второй период
                    set_time2.onchange = function() {
                        dt_2 = set_time2.value;
                        console.log(dt_2)
                        console.log(typeof(dt_1))
                        console.log(typeof(dt_1))
                        //проверили, введенные данные соответствуют формату STRING
                        //Значит для работы с ним их нужно привести в типу Datatime
                        time1 = new Date(dt_1);
                        time2 = new Date(dt_2);
                        console.log(typeof(time1))
                        console.log(typeof(time2))
                        //При новой проверке time 1, time 2 уже стали обьектами JavaScript
                        //Проверим любой обьект, чему он соответствует
                        console.log(typeof((data[948666].Date)))
                        // это тоже строка, ее мы будем перебирать и приводить в типу Datatime в цикле
                        //Проверим работает ли арифметика
                        time_ex = new Date(data[948666].Date)
                        console.log('json:', typeof((data)))
                        //здесь напишем, что код будет сразатывать при изменении одного из полей даты
                        var log_j = []
                        for (i in data) //Запускаем цикл для прохода по нашим данным
                        //В первую очередь нас интересуют данные за период времени
                        {
                            if ((new Date(data[i].Date) > time1) && (new Date(data[i].Date) < time2)) // это наша
                                выборка по периоду времени {
                                    log_j.push(data[i]);
                                }
                        }
                        let option_d;
                        let uName_arr = [];
                        for (i in log_j) {
                            uName_arr.push(log_j[i].uName)
                        }
                        //console.log(uName_arr)
                        var uName_set = new Set(uName_arr)
                        //console.log(uName_set)
                        var uName = Array.from(uName_set);
                        //console.log(uName)
                        //Теперь у нас есть массив log_j
                        /// Заполняем поле выбора прибора
                        for (i in uName) {
                            option_d = document.createElement('option');
                            option_d.text = uName[i];
                            option_d.value = uName[i];
                            device.add(option_d);
                        }
                        var set_device = document.getElementById("device");
                        set_device.onchange = function() {
                            _device = set_device.value;
                            //console.log(_device)
                            //У нас есть выбранный датчик, по нему получаем серийный номер
                            let option_sn;
                            let SN_Arr = [];
                            for (i in log_j) {
                                if (log_j[i].uName == _device) {
                                    SN_Arr.push(log_j[i].serial)
                                }
                            }
                            //Получили все серийные номера за период
                            //console.log(SN_Arr);
                            var SN_Set = new Set(SN_Arr);
                            var SN_List = Array.from(SN_Set);
                            //Заполняем поле серийного номера
                            for (i in SN_List) {
                                option_sn = document.createElement('option');
                                option_sn.text = SN_List[i];
                                option_sn.value = SN_List[i];
                                serial_number.add(option_sn);
                            }
                            //Добавили серийные номера
                            var set_sn = document.getElementById("sn");
                            set_sn.onchange = function() {
                                _sn = set_sn.value;
                                //console.log(_sn)
                                //Далее датчики
                                let sensor_Arr = [];
                                for (i in log_j) {
                                    if (log_j[i].uName == _device && log_j[i].serial == _sn) {
                                        sensor_Arr = Object.keys(log_j[i].data);
                                    }
                                }
                                var sensor_Set = new Set(sensor_Arr);
                                var sensor_List = Array.from(sensor_Set);
                                let option_sensor;
                                for (i in sensor_List) {
                                    option_sensor = document.createElement('option');
                                    option_sensor.text = sensor_List[i];
                                    option_sensor.value = sensor_List[i];
                                    sensor1.add(option_sensor);
                                }
                                for (i in sensor_List) {
                                    option_sensor = document.createElement('option');
                                    option_sensor.text = sensor_List[i];
                                    option_sensor.value = sensor_List[i];
                                    sensor2.add(option_sensor);
                                }
                                //Перехватываем выбор датчика
                                var set_sensor1 = document.getElementById("sensor1");
                                set_sensor1.onchange = function() {
                                    _sensor1 = set_sensor1.value;
                                    var set_sensor2 = document.getElementById("sensor2");
                                    set_sensor2.onchange = function() {
                                        _sensor2 = set_sensor2.value;
                                        const button = document.querySelector('.button');
                                        button.onclick = function() {
                                            //Заводим массивы для нашего графика
                                            let x_arr = [];
                                            let y_arr = [];
                                            let y_arr_h = [];
                                            let y_arr_t = [];
                                            for (i in log_j) {
                                                if (log_j[i].uName == _device && log_j[i].serial == _sn) {
                                                    x_arr.push(new Date(log_j[i].Date));
                                                    for (j in log_j[i].data) {
                                                        if (j == _sensor1) {
                                                            y_arr_t.push(parseFloat(log_j[i].data[j]));
                                                        }
                                                    }
                                                    for (j in log_j[i].data) {
                                                        if (j == _sensor2) {
                                                            y_arr_h.push(parseFloat(log_j[i].data[j]));
                                                        }
                                                    }
                                                }
                                            }
                                            for (i in x_arr) {
                                                y_arr.push(y_arr_t[i] - 0.4 * (y_arr_t[i] - 10) * (1 - y_arr_h[i] / 100))
                                            }
                                            //Как усреднить данные за час?
                                            // Всего скорее количество Х равно количеству часов в периоде
                                            // Складываем все У за этот час и делим на комичество измерений
                                            // Кладем их в новый массив// Значений должно быть меньше чем если
                                            строим по всем данным
                                            //Дальше графики любимые
                                            var trace = {
                                                x: x_arr,
                                                y: y_arr,
                                                type: 'line',
                                                name: _sensor1 + ' ' + _sensor2,
                                            };
                                            let oshush = [];
                                            var col = ' ';
                                            for (i in y_arr) {
                                                if (y_arr[i] >= -12 && y_arr[i] <= 0) {
                                                    oshush.push(0);
                                                    col = ('black')
                                                }
                                                if (y_arr[i] >= 0 && y_arr[i] <= 6) {
                                                    oshush.push(1);
                                                    col = ('gray')
                                                }
                                                if (y_arr[i] >= 6 && y_arr[i] <= 12) {
                                                    oshush.push(2);
                                                    col = ('yellow')
                                                }
                                                if (y_arr[i] >= 12 && y_arr[i] <= 18) {
                                                    oshush.push(3);
                                                    col = ('pink')
                                                }
                                                if (y_arr[i] >= 18 && y_arr[i] <= 24) {
                                                    oshush.push(4);
                                                    col = ('green')
                                                }
                                                if (y_arr[i] >= 24 && y_arr[i] <= 30) {
                                                    oshush.push(5);
                                                    col = ('red')
                                                }
                                                if (y_arr[i] > 30) {
                                                    oshush.push(6);
                                                    col = ('brown')
                                                }
                                            }
                                            var trace = {
                                                x: x_arr,
                                                y: y_arr,
                                                type: 'line',
                                                name: _sensor1 + ' ' + _sensor2,
                                            };
                                            var trace2 = {
                                                x: x_arr,
                                                y: oshush,
                                                type: 'line',
                                                type: 'scatter',
                                                name: _sensor1 + ' ' + _sensor2,
                                                fill: 'tonexty',
                                                fillcolor: col,
                                                marker: {
                                                    symbol: 'diamond',
                                                    size: 10
                                                }
                                            };
                                            // Добавляем данные во внешний массив
                                            plotData.push(trace);
                                            plotData_e.push(trace2);
                                            Plotly.newPlot('Div', plotData);
                                            Plotly.newPlot('mDiv', plotData_e);
                                            button.onclick //И кол бэк
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            });
        });
const button1 = document.querySelector('.res');
button1.onclick = function() {
    device.innerHTML = null;
    sn.innerHTML = null;
    sensor1.innerHTML = null;
    sensor2.innerHTML = null;
    device.add(device_option);
    device.selectedIndex = 0;
    serial_number.add(serial_number_option);
    serial_number.selectedIndex = 0;
    sensor1.add(sensor1_option);
    sensor1.selectedIndex = 0;
    sensor2.add(sensor2_option);
    sensor2.selectedIndex = 0;
    return true;
}
