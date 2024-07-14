async function fetchTemperatureData() {
    const loading = document.getElementById('loading');
    try {
        loading.classList.remove('hidden');
        const response = await fetch('https://16.16.70.116:65500/get');
        const data = await response.json();
        // Update temperature data
        document.getElementById('currentTemp').textContent = data.currentTemperature;
        document.getElementById('maxTemp').textContent = data.maximumTemperature;
        document.getElementById('minTemp').textContent = data.minimumTemperature;
        document.getElementById('notthreshold').textContent = data.notthreshold;
        // Update humidity data
        document.getElementById('currentHumidity').textContent = data.currentHumidity;
        document.getElementById('maxHumidity').textContent = data.maximumHumidity;
        document.getElementById('minHumidity').textContent = data.minimumHumidity;
        document.getElementById('humidityThreshold').textContent = data.humidityThreshold;
        // Update notification status
        document.getElementById('ennot').textContent = data.ennot;
    } catch (error) {
        console.error('Error fetching temperature data:', error);
    } finally {
        loading.classList.add('hidden');
    }
}
        function redirectToPostValues() {
            //window.location.href = 'post-values.html';
            window.location.href = 'register.html';
        }
// Fetch data immediately and then every 5 seconds
fetchTemperatureData();
setInterval(fetchTemperatureData, 5000);









      


