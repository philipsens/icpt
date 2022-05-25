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
