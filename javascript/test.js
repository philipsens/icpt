const style = {
    button: {
        phone: {
            width: 20,
        },
        tablet: {
            portrait: {
                width: 40,
            },
            landscape: {
                width: 60,
            },
        },
        screen: {
            width: 100,
        },
        width: 50,
        height: 50,
    },
    a: {
        background: 'grey',
        phone: {
            color: 'blue',
        },
        color: 'red'
    },
    div: {
        background: 'grey',
        phone: {
            transform: [{rotate: "45deg"}],
        },
        transform: [{rotate: "-45deg"}],
    }
};

function applyViewport(style, device, orientation) {
    const DEVICES = ['phone', 'tablet', 'screen', 'monitor']

    let newStyle = {}
    for (const key in style) {
        const item = style[key]

        const values = item[device]?.[orientation] ?? item[device]

        for (const key in values) {
            item[key] = values[key]
        }

        let newItem = {}
        for (const key in item) {
            if (!DEVICES.includes(key)) {
                newItem = {...newItem, [key]: item[key]}
            }
        }
        newStyle = {...newStyle, [key]: newItem}
    }
    return newStyle
}

test('phone portrait', () => {
    const expectedResult = JSON.stringify({
        "button": {"width": 20, "height": 50},
        "a": {"background": "grey", "color": "blue"},
        "div": {"background": "grey", "transform": [{"rotate": "45deg"}]}
    })

    const result = JSON.stringify(applyViewport(style, 'phone', 'portrait'))

    expect(result).toBe(expectedResult)
});


test('phone landscape', () => {
    const expectedResult = JSON.stringify({
        "button": {"width": 20, "height": 50},
        "a": {"background": "grey", "color": "blue"},
        "div": {"background": "grey", "transform": [{"rotate": "45deg"}]}
    })

    const result = JSON.stringify(applyViewport(style, 'phone', 'landscape'))

    expect(result).toBe(expectedResult)
});

test('tablet portrait', () => {
    const expectedResult = JSON.stringify({
        "button": {"width": 40, "height": 50},
        "a": {"background": "grey", "color": "red"},
        "div": {"background": "grey", "transform": [{"rotate": "-45deg"}]}
    })

    const result = JSON.stringify(applyViewport(style, 'tablet', 'portrait'))

    expect(result).toBe(expectedResult)
});

test('tablet landscape', () => {
    const expectedResult = JSON.stringify({
        "button": {"width": 60, "height": 50},
        "a": {"background": "grey", "color": "red"},
        "div": {"background": "grey", "transform": [{"rotate": "-45deg"}]}
    })

    const result = JSON.stringify(applyViewport(style, 'tablet', 'landscape'))

    expect(result).toBe(expectedResult)
});