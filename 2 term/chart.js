//Заполнение полей
let device = document.getElementById('device');
device.length = 0;
let serial_number = document.getElementById('sn');
serial_number.length = 0;
let sensor = document.getElementById('sensor');
sensor.length = 0;
let device_option = document.createElement('option');
device_option.text = 'Прибор';
let serial_number_option = document.createElement('option');
serial_number_option.text = 'С/Н';
let sensor_option = document.createElement('option');
sensor_option.text = 'Датчик';
device.add(device_option);
device.selectedIndex = 0;
serial_number.add(serial_number_option);
serial_number.selectedIndex = 0;
sensor.add(sensor_option);
sensor.selectedIndex = 0;
//Получение данных для парсинга
const url = '/data';
//Создаем Fetch запрос для поучения данных
var plotData = [];
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
                                    sensor.add(option_sensor);
                                }
                                //Перехватываем выбор датчика
                                var set_sensor = document.getElementById("sensor");
                                set_sensor.onchange = function() {
                                    _sensor = set_sensor.value;
                                    //console.log(_sensor)
                                    //Тут наш код продолжается вглубь
                                    const button = document.querySelector('.button');
                                    button.onclick = function() {
                                        sred = document.getElementById('sred').value
                                        //Заводим массивы для нашего графика
                                        let x_arr = [];
                                        let y_arr = [];
                                        let x_arr_h = [];
                                        let x_arr_hhh = [];
                                        x_arr_day = [];
                                        //let count = 0;
                                        //let all_value = 0;
                                        for (i in log_j) {
                                            if (log_j[i].uName == _device && log_j[i].serial == _sn && sred == 'asis') {
                                                x_arr.push(new Date(log_j[i].Date));
                                                for (j in log_j[i].data) {
                                                    if (j == _sensor) {
                                                        y_arr.push(parseFloat(log_j[i].data[j]));
                                                    }
                                                }
                                            }
                                            if (log_j[i].uName == _device && log_j[i].serial == _sn && sred == 'hour') { //осреднение по 1 часу
                                                //console.log()
                                                x_arr_h.push((new Date(log_j[i].Date)).getHours());
                                            }
                                            if (log_j[i].uName == _device && log_j[i].serial == _sn && sred == '3hour') { // осреднение по 3 часам
                                                //console.log()
                                                x_arr_hhh.push((new Date(log_j[i].Date)).getHours());
                                            }
                                            if (log_j[i].uName == _device && log_j[i].serial == _sn && sred == 'day' ||
                                                sred == 'mm') { // осреднение по суткам
                                                //console.log()
                                                x_arr_day.push((new Date(log_j[i].Date)).getDate());
                                            }
                                        }
                                        console.log(new Set(x_arr_day))
                                        //Как усреднить данные за час?
                                        // Всего скорее количество Х равно количеству часов в периоде
                                        // Складываем все У за этот час и делим на комичество измерений
                                        // Кладем их в новый массив// Значений должно быть меньше чем если
                                        строим по всем данным
                                        y_arr_h = [];
                                        //осреднение за каждый час(в пределах 1 суток)
                                        if (sred == 'hour') {
                                            x_arr_hh = Array.from(new Set(x_arr_h)); // получили ось X
                                            //теперь отберем Y
                                            console.log('x_arr:', (x_arr.length));
                                            for (var g = x_arr_hh[0]; g < (x_arr_hh.length + x_arr_hh[0]); g++) {
                                                value_h = 0;
                                                count = 0;
                                                console.log('g:', (g));
                                                for (i in log_j) {
                                                    if (log_j[i].uName == _device && log_j[i].serial == _sn && new Date(log_j[i].Date).getHours() == g) {
                                                        console.log('log_j:', log_j[i].data.weather_temp)
                                                        count++;
                                                        for (j in log_j[i].data) {
                                                            if (j == _sensor) {
                                                                value_h += parseFloat(log_j[i].data[j]);
                                                            }
                                                            //value_h = value_h + value_h;
                                                        }
                                                    }
                                                }
                                                //
                                                console.log('value:', (value_h));
                                                console.log('count:', (count));
                                                console.log('t_sr:', (value_h / count));
                                                console.log('dev:', typeof(device));
                                                y_arr.push(value_h / count)
                                            }
                                            for (i in x_arr_hh) {
                                                x_arr.push(new Date(time1.getFullYear(), time1.getMonth(),
                                                    time1.getDate(), x_arr_hh[i] + 1))
                                            }
                                        }
                                        //Осреднение за 3 часа (в пределах 1 суток)
                                        if (sred == '3hour') {
                                            x_arr_3hh = Array.from(new Set(x_arr_hhh)); // получили ось X
                                            let x_arr_3 = [];
                                            for (var i = x_arr_3hh[0]; i < (x_arr_3hh.length + x_arr_3hh[0]); i = i + 3) {
                                                x_arr_3.push(i)
                                            }
                                            //теперь отберем Y
                                            console.log('x_arr3:', (x_arr_3));
                                            for (var g = x_arr_3[0]; g < (x_arr_3.length + x_arr_3[0]); g++) {
                                                value_h = 0;
                                                count = 0;
                                                console.log('g:', (g));
                                                for (i in log_j) {
                                                    if (log_j[i].uName == _device && log_j[i].serial == _sn && new Date(log_j[i].Date).getHours() == g) {
                                                        console.log('log_j:', log_j[i].data.weather_temp)
                                                        count++;
                                                        for (j in log_j[i].data) {
                                                            if (j == _sensor) {
                                                                value_h += parseFloat(log_j[i].data[j]);
                                                            }
                                                            //value_h = value_h + value_h;
                                                        }
                                                    }
                                                }
                                                //
                                                console.log('value:', (value_h));
                                                console.log('count:', (count));
                                                console.log('t_sr:', (value_h / count));
                                                console.log('dev:', typeof(device));
                                                y_arr.push(value_h / count)
                                            }
                                            for (i in x_arr_3) {
                                                x_arr.push(new Date(time1.getFullYear(), time1.getMonth(),
                                                    time1.getDate(), x_arr_3[i] + 3))
                                            }
                                        }
                                        //осреднение за сутки(в пределах 1 месяца)
                                        if (sred == 'day') {
                                            x_arr_dd = Array.from(new Set(x_arr_day)); // получили ось X
                                            //теперь отберем Y
                                            console.log('x_arr:', (x_arr_dd));
                                            for (var g = x_arr_dd[0]; g < (x_arr_dd.length + x_arr_dd[0]); g++) {
                                                value_h = 0;
                                                count = 0;
                                                console.log('g:', (g));
                                                for (i in log_j) {
                                                    if (log_j[i].uName == _device && log_j[i].serial == _sn && new Date(log_j[i].Date).getDate() == g) {
                                                        console.log('log_j:', log_j[i].data.weather_temp)
                                                        count++;
                                                        for (j in log_j[i].data) {
                                                            if (j == _sensor) {
                                                                value_h += parseFloat(log_j[i].data[j]);
                                                            }
                                                            //value_h = value_h + value_h;
                                                        }
                                                    }
                                                }
                                                //
                                                console.log('value:', (value_h));
                                                console.log('count:', (count));
                                                console.log('t_sr:', (value_h / count));
                                                console.log('dev:', typeof(device));
                                                y_arr.push(value_h / count)
                                            }
                                            for (i in x_arr_dd) {
                                                x_arr.push(new Date(time1.getFullYear(), time1.getMonth(), x_arr_dd[i] +
                                                    1))
                                            }
                                        }
                                        let y_arr_max = [];
                                        let y_arr_min = [];
                                        if (sred == 'mm') {
                                            x_arr_dd = Array.from(new Set(x_arr_day)); // получили ось X
                                            //теперь отберем Y
                                            console.log('x_arr:', (x_arr_dd));
                                            for (var g = x_arr_dd[0]; g < (x_arr_dd.length + x_arr_dd[0]); g++) {
                                                value_m = [];
                                                count = 0;
                                                console.log('g:', (g));
                                                for (i in log_j) {
                                                    if (log_j[i].uName == _device && log_j[i].serial == _sn && new Date(log_j[i].Date).getDate() == g) {
                                                        //console.log('log_j:',log_j[i].data.weather_temp)
                                                        count++;
                                                        for (j in log_j[i].data) {
                                                            if (j == _sensor) {
                                                                value_m.push(log_j[i].data[j]);
                                                            }
                                                            //value_h = value_h + value_h;
                                                        }
                                                    }
                                                }
                                                //
                                                console.log('value:', (value_m));
                                                //console.log('count:', (count));
                                                //console.log('t_sr:', (value_h/count));
                                                console.log('dev:', typeof(device));
                                                y_arr_max.push(Math.max.apply(null, value_m));
                                                y_arr_min.push(Math.min.apply(null, value_m));
                                            }
                                            for (i in x_arr_dd) {
                                                x_arr.push(new Date(time1.getFullYear(), time1.getMonth(), x_arr_dd[i] +
                                                    1))
                                            }
                                        }
                                        console.log('YY', y_arr_max)
                                        console.log('YY', y_arr_min)
                                        typet = document.getElementById('type').value
                                        //Дальше графики любимые
                                        if (typet == 'any') {
                                            var trace1 = {
                                                x: x_arr,
                                                y: y_arr,
                                                type: typet,
                                                mode: 'markers',
                                                name: _sensor + ' ' + sred,
                                            };
                                        } else {
                                            var trace1 = {
                                                x: x_arr,
                                                y: y_arr,
                                                type: typet,
                                                name: _sensor + ' ' + sred,
                                            };
                                        }
                                        if (sred == 'mm') {
                                            var trace2 = {
                                                x: x_arr,
                                                y: y_arr_max,
                                                type: typet,
                                                name: _sensor + ' ' + 'Максимум',
                                                type: 'line',
                                            }
                                            var trace3 = {
                                                x: x_arr,
                                                y: y_arr_min,
                                                type: typet,
                                                name: _sensor + ' ' + 'Минимум',
                                                type: 'line',
                                            }
                                            // Добавляем данные во внешний массив
                                            plotData.push(trace1, trace2, trace3);
                                        } else {
                                            plotData.push(trace1);
                                        }
                                        //Строим графики из массива
                                        Plotly.newPlot('Div', plotData);
                                        console.log(y_arr)
                                        console.log(x_arr)
                                        console.log(Math.max.apply(null, y_arr))
                                        button.onclick //И кол бэк
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
    sensor.innerHTML = null;
    device.add(device_option);
    device.selectedIndex = 0;
    serial_number.add(serial_number_option);
    serial_number.selectedIndex = 0;
    sensor.add(sensor_option);
    sensor.selectedIndex = 0;
    return true;
}
