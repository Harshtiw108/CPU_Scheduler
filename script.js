document.getElementById('algorithm').addEventListener('change', function() {
    if (this.value === 'rr') {
        document.getElementById('quantum').style.display = 'block';
        document.getElementById('quantumLabel').style.display = 'block';
    } else {
        document.getElementById('quantum').style.display = 'none';
        document.getElementById('quantumLabel').style.display = 'none';
    }
});

async function simulateScheduling() {
    const algorithm = document.getElementById('algorithm').value;
    const processInput = document.getElementById('processes').value.trim();
    const quantum = parseInt(document.getElementById('quantum').value);

    if (!processInput) {
        alert("Please enter process details.");
        return;
    }

    const processes = processInput.split('\n').map(line => {
        const [pid, burstTime, priority] = line.split(',').map(Number);
        return { pid, burstTime, priority };
    });

    const requestBody = { algorithm, processes };
    if (algorithm === 'rr') {
        if (isNaN(quantum) || quantum < 1) {
            alert("Please enter a valid time quantum for Round Robin scheduling.");
            return;
        }
        requestBody.quantum = quantum;
    }

    const response = await fetch('/schedule', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(requestBody)
    });

    const result = await response.json();
    displayResults(result);
}

function displayResults(results) {
    let output = '<table><tr><th>Process</th><th>Burst Time</th><th>Priority</th><th>Waiting Time</th><th>Turnaround Time</th></tr>';
    results.forEach(process => {
        output += `<tr>
                    <td>${process.pid}</td>
                    <td>${process.burstTime}</td>
                    <td>${process.priority}</td>
                    <td>${process.waitingTime}</td>
                    <td>${process.turnAroundTime}</td>
                   </tr>`;
    });
    output += '</table>';
    document.getElementById('results').innerHTML = output;
}
