
async function submitValue(field) {
    const formData = new FormData();
    formData.append(field, document.getElementById(field).value);
    try {
        const response = await fetch('https://16.16.70.116:65500/post', {
            method: 'POST',
            body: formData
        });
        if (response.ok) {
            const responseData = await response.json();
            document.getElementById('response').textContent = responseData.message;
        } else {
            throw new Error('Failed to post value');
        }
    } catch (error) {
        console.error('Error posting value:', error);
        document.getElementById('response').textContent = 'Error: ' + error.message;
    }
}

async function submitSwitch() {
    const formData = new FormData();
    formData.append('switch', document.getElementById('switch').checked ? 'on' : 'off');
    try {
        const response = await fetch('https://16.16.70.116:65500/post', {
            method: 'POST',
            body: formData
        });
        if (response.ok) {
            const responseData = await response.json();
            document.getElementById('response').textContent = responseData.message;
        } else {
            throw new Error('Failed to post switch value');
        }
    } catch (error) {
        console.error('Error posting switch value:', error);
        document.getElementById('response').textContent = 'Error: ' + error.message;
    }

}



        function redirectToMain() {
            window.location.href = 'index.html';
        }

document.getElementById('switch').addEventListener('change', submitSwitch);
submitValue(field);
setInterval(submitValue(field), 2000);
submitSwitch();
setInterval(submitSwitch(), 2000);
