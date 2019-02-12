using UnityEngine;

public sealed class WaitForThread : CustomYieldInstruction
{
    private bool done = false;

    public override bool keepWaiting
    {
        get { return !done; }
    }

    public void OnDone()
    {
        done = true;
    }
}