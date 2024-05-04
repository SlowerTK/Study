function submit() {
    let selectedProducts = [];
    let checkboxes = document.querySelectorAll('input[type=checkbox]');
    let sum = 0;

    for (let i = 0; i < checkboxes.length; i++) {
        if (checkboxes[i].checked) {
            let count = document.getElementById(checkboxes[i].id + '_').value;
            selectedProducts.push({ id: checkboxes[i].id, count: count });
            sum += document.getElementById(checkboxes[i].id + '_').value;
        }
    }
    if (selectedProducts.length == 0 || sum == 0) {
        alert('Вы не выбрали ни одного товара!');
        return;
    }

    let json = JSON.stringify(selectedProducts);

    fetch('http://127.0.0.1:5000/submit', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: json
    })
        .then(response => {
            if (!response.ok) {
                return response.json().then(error => { throw new Error(error.message); });
            }
            return response.json();
        })
        .then(data => {
            if (data.status === 'success') {
                alert('Заказ успешно оформлен!');
                location.reload();
            }
        })
        .catch(error => {
            alert('Ошибка: ' + error.message);
        });
}

window.onload = function () {
    for (let i = 1; i <= 4; i++) {
        let productId = i;
        fetch(`http://127.0.0.1:5000/get_count?id=${productId}`)
            .then(response => response.json())
            .then(data => {
                let count = data.count;
                let element = document.getElementById(`${productId}__`);
                element.innerHTML = 'Остаток на складе: ' + count;
                if (count == 0) {
                    element.disabled = true;
                    document.getElementById(`${productId}`).disabled = true;
                    document.getElementById(`${productId}_`).disabled = true;
                }
            });
    }
}